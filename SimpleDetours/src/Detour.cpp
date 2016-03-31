#include "Detour.h"
using namespace SimpleDetours;
using namespace std;

void SimpleDetours::Detour::setupHook()
{
	if(isDeployed)
		return;
	
	originalBytes = new byte[originalBytesSize]();
	putMemory(originalBytes, place, originalBytesSize);

	dword argsCount = 0;
	byte* args = NULL;
	if (arguments != "")
	{
		argsCount = argsCountBytes(',');
		if (argsCount != 0)
		{
			args = new byte[argsCount];
			argsParse(args, argsCount);
		}
	}

	//calculate detour code size
	detourCodeSize = 20 + originalBytesSize + argsCount;
	detourCode = VirtualAlloc(NULL, detourCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE); //TODO: check flags

	dword j = 0;

	putOpcode_byte(detourCode, j, OP_PUSHAD);                              // pushad
	putOpcode_byte(detourCode, j, OP_PUSHFD);                              // pushfd
	for (dword i = 0; i < argsCount; ++i)                                  // push <REGISTER>
		putOpcode_byte(detourCode, j, args[i]);
	putOpcode_byte(detourCode, j, OP_MOV_EAX_M32);                         // mov eax, 
	putOpcode_dword(detourCode, j, targetAddress.d());                     //          hookAddress
	putOpcode_word(detourCode, j, OP_CALL_EAX);                            // call eax
	putOpcode_byte(detourCode, j, OP_POPFD);                               // popfd
	putOpcode_byte(detourCode, j, OP_POPAD);                               // popad
	memcpy_s((detourCode + j).vp(), detourCodeSize - j, originalBytes.vp(), originalBytesSize); //execute original bytes
	j += originalBytesSize;
	putOpcode_byte(detourCode, j, OP_PUSH_M32);                            // push	
	putOpcode_dword(detourCode, j, place.d() + originalBytesSize);         //       <return address>
	putOpcode_byte(detourCode, j, OP_RET);                                 // ret

	if (j != detourCodeSize)
		/*BREAKPOINT*/;

	setByte(place, OP_JMP);
	setDword(place + 1, (detourCode - place).d() + 5); //TODO: check if -5

	if (args)
		delete[] args;
		
		isDeployed = true;
}

void SimpleDetours::Detour::removeHook()
{
	if(!isDeployed)
		return;
		
	setMemory(place, originalBytes, originalBytesSize);
	delete[] originalBytes.vp();
	VirtualFree(detourCode.vp(), detourCodeSize, MEM_RELEASE);
	
	isDeployed = false;
}

dword SimpleDetours::Detour::version()
{
	return static_cast<dword>(DETOUR_VERSION);
}

SimpleDetours::Detour::Detour()
{
	place = NULL;
	originalBytes = NULL;
	originalBytesSize = 0;
	targetAddress = NULL;
	detourCode = NULL;
	detourCodeSize = 0;
	arguments = "";
}

SimpleDetours::Detour::Detour(MultiPointer address, dword size, MultiPointer hookAddress, std::string& pushArguments) : Detour()
{
	place = address;
	originalBytesSize = size;
	targetAddress = hookAddress;
	arguments = pushArguments;

	setupHook();
}

SimpleDetours::Detour::~Detour()
{
	removeHook();
}

dword SimpleDetours::Detour::argsCountBytes(byte b)
{
	dword result = 0;
	dword start = 0;
	dword end = arguments.find(b, 0);

	while (end != string::npos) {
		++result;
		start = end;
		end = arguments.find(b, start);
	}

	return result;
}

void SimpleDetours::Detour::argsParse(byte* arr, dword count)
{
	if (count == 1)
	{
		arr[0] = getPushRegisterOpcodeForName(arguments);
	}
	else
	{
		dword idx = 0;
		dword end = arguments.length();
		dword start = arguments.rfind(',');
		while (start != string::npos)
		{
			arr[idx] = getPushRegisterOpcodeForName(arguments.substr(start, end - start)); //TODO: test string
			++idx;
			end = start;
			start = arguments.rfind(',', end);
		}

		if (idx != count)
			;//TODO: error
	}
}

SimpleDetours::byte SimpleDetours::Detour::getPushRegisterOpcodeForName(string& name)
{
	if (name == "eax")
		return OP_PUSH_EAX;
	else if (name == "ebx")
		return OP_PUSH_EBX;
	else if (name == "ecx")
		return OP_PUSH_ECX;
	else if (name == "edx")
		return OP_PUSH_EDX;
	else if (name == "esp")
		return OP_PUSH_ESP;
	else if (name == "edi")
		return OP_PUSH_EDI;
	else if (name == "ebp")
		return OP_PUSH_EBP;
	else if (name == "esi")
		return OP_PUSH_ESI;

	return 0;
}

inline void SimpleDetours::Detour::putOpcode_byte(MultiPointer address, dword& offset, byte b)
{
	putByte(address.d() + offset, b);
	++offset;
}

inline void SimpleDetours::Detour::putOpcode_word(MultiPointer address, dword& offset, word w)
{
	putWord(address.d() + offset, w);
	offset += sizeof(word);
}

inline void SimpleDetours::Detour::putOpcode_dword(MultiPointer address, dword& offset, dword d)
{
	putDword(address.d() + offset, d);
	offset += sizeof(dword);
}