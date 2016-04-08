#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class NopHook : public HookBase
	{
	public:
		NopHook();
		NopHook(MultiPointer target, dword size);
		~NopHook();
		
		void initialize(MultiPointer target, dword size);
		void setupHook();
		void removeHook();
	private:
		MultiPointer place;
		MultiPointer originalBytes;
		dword originalBytesSize;
	};
}
