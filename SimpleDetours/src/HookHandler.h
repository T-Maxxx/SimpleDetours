#pragma once
#include "AllHooks.h"
#include <stack>
#include <string>

namespace SimpleDetours
{
	class HookHandler
	{
	public:
		HookHandler();
		~HookHandler();

		inline void addByteHook(MultiPointer place, byte b);
		inline void addWordHook(MultiPointer place, word w);
		inline void addDwordHook(MultiPointer place, dword d);
		inline void addMemoryHook(MultiPointer place, MultiPointer memory, dword memSize);
		inline void addDetour(MultiPointer place, MultiPointer retAddr, MultiPointer detour, std::string args);

	private:
		std::stack<ByteHook*>*   stByteHooks;
		std::stack<WordHook*>*   stWordHooks;
		std::stack<DwordHook*>*  stDwordHooks;
		std::stack<MemoryHook*>* stMemoryHooks;
		std::stack<Detour*>*     stDetours;
	};
}
