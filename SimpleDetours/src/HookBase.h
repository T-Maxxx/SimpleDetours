#pragma once
#include <Windows.h>
#include "MultiPointer.h"

namespace SimpleDetours
{
	class HookBase
	{
	public:
		HookBase();

		virtual void setupHook() = 0;
		virtual void removeHook() = 0;
		virtual dword version() = 0;

	protected:
		bool isDeployed;
		//Application memory
		static byte   setByte(MultiPointer address, byte b);
		static word   setWord(MultiPointer address, word w);
		static dword setDword(MultiPointer address, dword d);
		static void setMemory(MultiPointer to, MultiPointer from, dword size);
		//Byte array
		static byte   putByte(MultiPointer address, byte b);
		static word   putWord(MultiPointer address, word w);
		static dword putDword(MultiPointer address, dword d);
		static void putMemory(MultiPointer to, MultiPointer from, dword size);

	private:
		static dword protectAddress(MultiPointer address, dword size, dword flags);
	};
}
