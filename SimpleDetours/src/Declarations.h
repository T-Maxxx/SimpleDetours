#pragma once
#define DETOUR_VERSION (1)
#define MEMORYHOOK_VERSION (1)
#define BYTEHOOK_VERSION (1)
#define WORDHOOK_VERSION (1)
#define DWORDHOOK_VERSION (1)
#define JUMPHOOK_VERSION (1)
#define CALLHOOK_VERSION (1)

#ifdef SIMPLEDETOURS_RUNTIME
#define SIMPLEDETOURS_API _declspec(dllimport)
#else
#define SIMPLEDETOURS_API _declspec(dllexport)
#endif

#ifdef SIMPLEDETOURS_PURECODE
#undef SIMPLEDETOURS_API
#define SIMPLEDETOURS_API
#endif

namespace SimpleDetours
{
	typedef unsigned char      byte;
	typedef unsigned short int word;
	typedef unsigned long int  dword;
	typedef void*              ptr;
	typedef char*              str;

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

		OP_ADD_R32_M32 = 0x81,
		OP_ADD_R32_EAX = 0xC0,
		OP_ADD_R32_ECX = 0xC1,
		OP_ADD_R32_EDX = 0xC2,
		OP_ADD_R32_EBX = 0xC3,
		OP_ADD_R32_ESP = 0xC4,
		OP_ADD_R32_EBP = 0xC5,
		OP_ADD_R32_ESI = 0xC6,
		OP_ADD_R32_EDI = 0xC7,


		OP_NOP = 0x90,
		OP_PUSHFD = 0x9C,
		OP_POPFD = 0x9D,
		OP_MOV_EAX_M32 = 0xB8,
		OP_RET = 0xC3,
		OP_CALL = 0xE8,
		OP_JMP = 0xE9,
		OP_CALL_EAX = 0xD0FF
	};
}