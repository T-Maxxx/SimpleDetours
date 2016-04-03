#pragma once
#include "HookBase.h"
#include <string>

namespace SimpleDetours
{	
	class SIMPLEDETOURS_API Detour : public HookBase
	{
	public:
		Detour();
		Detour(MultiPointer address, MultiPointer returnAddress, MultiPointer hookAddress, str pushArguments);
		~Detour();

		void initialize(MultiPointer address, MultiPointer returnAddress, MultiPointer hookAddress, str pushArguments);
		void setupHook();
		void removeHook();
		dword version();

	private:
		MultiPointer place;
		MultiPointer retAddr;
		MultiPointer originalBytes;
		dword originalBytesSize;
		MultiPointer targetAddress;
		MultiPointer detourCode;
		dword detourCodeSize;
		str arguments;

		dword argsCountBytes(byte b);
		void argsParse(byte* arr, dword count);
		byte getPushRegisterOpcodeForName(std::string& name);
		//Note: offset will be changed
		static inline void  putOpcode_byte(MultiPointer address, dword &offset, byte b);
		static inline void  putOpcode_word(MultiPointer address, dword &offset, word w);
		static inline void putOpcode_dword(MultiPointer address, dword &offset, dword d);

	};

}