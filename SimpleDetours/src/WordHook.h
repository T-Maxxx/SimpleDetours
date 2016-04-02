#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class SIMPLEDETOURS_API WordHook: public HookBase
	{
	public:
		WordHook();
		WordHook(MultiPointer to, word w);
		~WordHook();
		
		void initialize(MultiPointer to, word w);
		void setupHook();
		void removeHook();
		dword version();
	private:
		MultiPointer place;
		word original;
		word replace;
	};
}
