#pragma once
#include "HookBase.h"
#include <string>

namespace SimpleDetours
{	
	enum Opcode
	{
		OP_PUSH_EAX = 0x50,
		OP_PUSH_ECX = 0x51,
		OP_PUSH_EDX = 0x52,
		OP_PUSH_EBX = 0x53,
		OP_PUSH_ESP = 0x54,
		OP_PUSH_EBP = 0x55,
		OP_PUSH_ESI = 0x56,
		OP_PUSH_EDI = 0x57,
		OP_PUSHAD = 0x60,
		OP_POPAD = 0x61,
		OP_PUSH_M32 = 0x68,
		OP_NOP = 0x90,
		OP_PUSHFD = 0x9C,
		OP_POPFD = 0x9D,
		OP_MOV_EAX_M32 = 0xB8,
		OP_RET = 0xC3,
		OP_CALL = 0xE8,
		OP_JMP = 0xE9,
		OP_CALL_EAX = 0xD0FF
	};

	class Detour : public HookBase
	{
	public:
		Detour();
		Detour(MultiPointer address, dword size, MultiPointer hookAddress, std::string pushArguments);
		~Detour();

		void initialize(MultiPointer address, dword size, MultiPointer hookAddress, std::string pushArguments);
		void setupHook();
		void removeHook();
		dword version();

	private:
		MultiPointer place;
		MultiPointer originalBytes;
		dword originalBytesSize;
		MultiPointer targetAddress;
		MultiPointer detourCode;
		dword detourCodeSize;
		std::string arguments;

		dword argsCountBytes(byte b);
		void argsParse(byte* arr, dword count);
		byte getPushRegisterOpcodeForName(std::string& name);
		//Note: offset will be changed
		static inline void  putOpcode_byte(MultiPointer address, dword &offset, byte b);
		static inline void  putOpcode_word(MultiPointer address, dword &offset, word w);
		static inline void putOpcode_dword(MultiPointer address, dword &offset, dword d);

	};

}