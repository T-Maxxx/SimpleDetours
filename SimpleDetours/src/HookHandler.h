#pragma once
#include "AllHeaders.h"
#include <stack>
#include <string>

namespace SimpleDetours
{
	class SIMPLEDETOURS_API HookHandler
	{
	public:
		HookHandler();
		~HookHandler();

		void addByteHook(MultiPointer place, byte b);
		void addWordHook(MultiPointer place, word w);
		void addDwordHook(MultiPointer place, dword d);
		void addMemoryHook(MultiPointer place, MultiPointer memory, dword memSize);
		void addDetour(MultiPointer place, MultiPointer retAddr, MultiPointer detour, str args);

	private:
		std::stack<ByteHook*>*   stByteHooks;
		std::stack<WordHook*>*   stWordHooks;
		std::stack<DwordHook*>*  stDwordHooks;
		std::stack<MemoryHook*>* stMemoryHooks;
		std::stack<Detour*>*     stDetours;
	};
}
