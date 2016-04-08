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
	ArgsInfo argsInfo(pushArguments);

	originalBytes = new byte[originalBytesSize]();
	putMemory(originalBytes, place, originalBytesSize);

	dword argumentsTotalSize = getPushArgumentsRawCodeSize(&argsInfo);
	dword argumentsCount = argsInfo.getArgumentsCount();

	//detourCodeSize = opcodes + push arguments size + original bytes count + esp cleanup(0 or 6)
	detourCodeSize = 17 + argumentsTotalSize + originalBytesSize + (argumentsTotalSize ? 6 : 0);
	detourCode = VirtualAlloc(NULL, detourCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE); //TODO: check flags

	dword j = 0;

	putOpcode_byte(detourCode, j, OP_PUSHAD);                              // pushad
	putOpcode_byte(detourCode, j, OP_PUSHFD);                              // pushfd
	for (dword i = argumentsCount - 1; i >= 0; --i) {                      // [push <REGISTERS>]
		byte buffer[7];
		dword actualBuffSize = 0;
		getPushRawCode(&argsInfo, i, buffer, &actualBuffSize);
		putOpcode_memory(detourCode, j, buffer, actualBuffSize);
	}
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

void SimpleDetours::Detour::getPushArgumentsRawCodeSize(ArgsInfo& argsInfo)
{
	dword result = 0;
	dword argsCount = argsInfo->getArgumentsCount();
	for(dword i = 0; i < argsCount; ++i)
	{
		byte ast = argsInfo[i].storingType;
		if(ast == AST_STACK)
			;///
		else if(ast >= AST_REG_EAX && ast <= AST_REG_ESI)
		{
			if(argsInfo[i].regOffset)
				result += 7;
			else
				retult += 1;
		}
		else
		{
			//TODO: error: AST_ERROR
		}
	}
	return result;
}

void SimpleDetours::Detour::getPushRawCode(ArgsInfo* argsInfo, dword index, byte* buff, dword* buffSize)
{
	if(index < 0 || index > argsInfo->getArgumentsCount())
		return; //TODO: error
	int j = 0;
	if(argsInfo[index].regOffset)
	{
		putOpcode_byte(buff, j, OP_ADD_R32_M32);s
		putOpcode_byte(buff, j, getAddRegisterForAST(argsInfo[index].storingType));
		putOpcode_dword(buff, j, argsInfo[index].regOffset);
		putOpcode_byte(buff, j, getPushRegisterForAST(argsInfo[index].storingType));s
	}
	else
		putOpcode_byte(buff, j, getPushRegisterForAST(argsInfo[index].storingType));
		
	*buffSize = j;
}

byte SimpleDetours::Detour::getAddRegisterForAST(byte ast)
{
	if(ast == AST_STACK)
		return OP_NOP; //TODO: add error.
		
	if(ast == AST_REG_EAX)
		return OP_ADD_R32_EAX;
	else if (ast == AST_REG_ECX)
		return OP_ADD_R32_ECX;
	else if (ast == AST_REG_EDX)
		return OP_ADD_R32_EDX;
	else if (ast == AST_REG_EBX)
		return OP_ADD_R32_EBX;
	else if (ast == AST_REG_ESP)
		return OP_ADD_R32_ESP;
	else if (ast == AST_REG_EBP)
		return OP_ADD_R32_EBP;
	else if (ast == AST_REG_ESI)
		return OP_ADD_R32_ESI;
	else if (ast == AST_REG_EDI)
		return OP_ADD_R32_EDI;
		
	return OP_NOP;
}

byte SimpleDetours::Detour::getPushRegisterForAST(byte ast)
{
	if(ast == AST_STACK)
		return OP_NOP; //TODO: error
	
	if(ast == AST_REG_EAX)
		return OP_PUSH_EAX;
	else if (ast == AST_REG_ECX)
		return OP_PUSH_ECX;
	else if (ast == AST_REG_EDX)
		return OP_PUSH_EDX;
	else if (ast == AST_REG_EBX)
		return OP_PUSH_EBX;
	else if (ast == AST_REG_ESP)
		return OP_PUSH_ESP;
	else if (ast == AST_REG_EBP)
		return OP_PUSH_EBP;
	else if (ast == AST_REG_ESI)
		return OP_PUSH_ESI;
	else if (ast == AST_REG_EDI)
		return OP_PUSH_EDI;
		
	return OP_NOP;
}
