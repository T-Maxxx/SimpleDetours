#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class MemoryHook : public HookBase
	{
	public:
		MemoryHook();
		MemoryHook(MultiPointer to, MultiPointer from, dword size);
		~MemoryHook();

		void initialize(MultiPointer to, MultiPointer from, dword size);
		void setupHook();
		void removeHook();
		dword version();
		
	private:
		MultiPointer originalBytes;
		dword originalBytesSize;
		MultiPointer place;
		MultiPointer memory;
		dword memorySize;
	};
}
