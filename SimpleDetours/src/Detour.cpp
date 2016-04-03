#include "Detour.h"
using namespace SimpleDetours;
using namespace std;

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

SimpleDetours::Detour::Detour(MultiPointer address, MultiPointer returnAddress, MultiPointer hookAddress, str pushArguments) : Detour()
{
	initialize(address, returnAddress, hookAddress, pushArguments);
	setupHook();
}

SimpleDetours::Detour::~Detour()
{
	removeHook();

	delete[] originalBytes.vp();
	VirtualFree(detourCode.vp(), detourCodeSize, MEM_RELEASE);
}

void SimpleDetours::Detour::initialize(MultiPointer address, MultiPointer returnAddress, MultiPointer hookAddress, str pushArguments)
{
	if (isInitialized)
		return;

	if ((returnAddress - address).d() < 5)
		return;

	place = address;
	retAddr = returnAddress;
	originalBytesSize = (retAddr - place).d();
	targetAddress = hookAddress;
	arguments = pushArguments;
	ArgumentsInfo argumentsInfo;

	originalBytes = new byte[originalBytesSize]();
	putMemory(originalBytes, place, originalBytesSize);

	argumentsInfo.parse(arguments);
	dword argumentsTotalSize = argumentsInfo.getTotalSize();
	dword argumentsCount = argumentsInfo.getArgumentsCount();

	//detourCodeSize = opcodes + push arguments size + original bytes count + (0 or 6)
	detourCodeSize = 17 + argumentsTotalSize + originalBytesSize + (argumentsTotalSize ? 6 : 0);
	detourCode = VirtualAlloc(NULL, detourCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE); //TODO: check flags

	dword j = 0;

	putOpcode_byte(detourCode, j, OP_PUSHAD);                              // pushad
	putOpcode_byte(detourCode, j, OP_PUSHFD);                              // pushfd
	for (dword i = 0; i < argumentsCount; ++i)                             // [push <REGISTERS>]
		putOpcode_memory(detourCode, j, argumentsInfo.getRawCode(i), argumentsInfo.getRawCodeSize(i));
	putOpcode_byte(detourCode, j, OP_MOV_EAX_M32);                         // mov eax, 
	putOpcode_dword(detourCode, j, targetAddress.d());                     //          hookAddress
	putOpcode_word(detourCode, j, OP_CALL_EAX);                            // call eax
	if (argumentsCount)                                                    // [add esp, 4*argumentsCount]
	{
		putOpcode_byte(detourCode, j, OP_ADD_R32_M32);                     // add
		putOpcode_byte(detourCode, j, OP_ADD_R32_ESP);                     //     esp, 
		putOpcode_dword(detourCode, j, 4*argumentsCount);                  //          4*argumentsCount
	}
	putOpcode_byte(detourCode, j, OP_POPFD);                               // popfd
	putOpcode_byte(detourCode, j, OP_POPAD);                               // popad
	memcpy_s((detourCode + j).vp(), detourCodeSize - j, originalBytes.vp(), originalBytesSize); //execute original bytes
	j += originalBytesSize;
	putOpcode_byte(detourCode, j, OP_PUSH_M32);                            // push	
	putOpcode_dword(detourCode, j, retAddr.d());                           //      <return address>
	putOpcode_byte(detourCode, j, OP_RET);                                 // ret

	if (j != detourCodeSize)
	{
		VirtualFree(detourCode.vp(), detourCodeSize, MEM_RELEASE);
		return;
	}

	isInitialized = true;
}

void SimpleDetours::Detour::setupHook()
{
	if(isDeployed || !isInitialized)
		return;
	
	setBytes(place, (retAddr - place).d(), OP_NOP);
	setByte(place, OP_JMP);
	setDword(place + 1, (detourCode - place).d() - 5);
		
	isDeployed = true;
}

void SimpleDetours::Detour::removeHook()
{
	if (!isDeployed || !isInitialized)
		return;
		
	setMemory(place, originalBytes, originalBytesSize);
		
	isDeployed = false;
}

dword SimpleDetours::Detour::version()
{
	return static_cast<dword>(DETOUR_VERSION);
}

void SimpleDetours::Detour::putOpcode_byte(MultiPointer address, dword& offset, byte b)
{
	putByte(address.d() + offset, b);
	++offset;
}

void SimpleDetours::Detour::putOpcode_word(MultiPointer address, dword& offset, word w)
{
	putWord(address.d() + offset, w);
	offset += sizeof(word);
}

void SimpleDetours::Detour::putOpcode_dword(MultiPointer address, dword& offset, dword d)
{
	putDword(address.d() + offset, d);
	offset += sizeof(dword);
}

void SimpleDetours::Detour::putOpcode_memory(MultiPointer to, dword & offset, MultiPointer from, dword size)
{
	putMemory(to.d() + offset, from, size);
	offset += size;
}
