#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class WordHook: public HookBase
	{
	public:
		WordHook();
		WordHook(MultiPointer to, word w);
		~WordHook();
		
		void setupHook();
		void removeHook();
		dword version();
	private:
		MultiPointer place;
		word original;
		word replace;
	};
}
