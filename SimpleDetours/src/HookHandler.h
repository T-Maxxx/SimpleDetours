#pragma once
#include "ByteHook.h"
#include "WordHook.h"
#include "DwordHook.h"
#include "MemoryHook.h"
#include "Detour.h"
#include <stack>
#include <string>

namespace SimpleDetours
{
	class HookHandler
	{
	public:
		HookHandler();
		~HookHandler();

		void addByteHook(MultiPointer place, byte b);
		void addWordHook(MultiPointer place, word w);
		void addDwordHook(MultiPointer place, dword d);
		void addMemoryHook(MultiPointer place, MultiPointer memory, dword memSize);
		void addDetour(MultiPointer place, MultiPointer retAddr, MultiPointer detour, std::string args);

	private:
		std::stack<ByteHook*>*   stByteHooks;
		std::stack<WordHook*>*   stWordHooks;
		std::stack<DwordHook*>*  stDwordHooks;
		std::stack<MemoryHook*>* stMemoryHooks;
		std::stack<Detour*>*     stDetours;
	};
}
