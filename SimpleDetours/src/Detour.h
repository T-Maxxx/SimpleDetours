#pragma once
#include "HookBase.h"
#include "ArgumentsInfo.h"
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

		//Note: offset will be changed
		static void  putOpcode_byte(MultiPointer address, dword &offset, byte b);
		static void  putOpcode_word(MultiPointer address, dword &offset, word w);
		static void putOpcode_dword(MultiPointer address, dword &offset, dword d);
		static void putOpcode_memory(MultiPointer to, dword& offset, MultiPointer from, dword size);
	};

}