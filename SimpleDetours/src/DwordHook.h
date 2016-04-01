#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class DwordHook : public HookBase
	{
	public:
		DwordHook();
		DwordHook(MultiPointer to, dword d);
		~DwordHook();
		
		void initialize(MultiPointer to, dword d);
		void setupHook();
		void removeHook();
		dword version();
		
	private:
		MultiPointer place;
		dword original;
		dword replace;
	};
}
