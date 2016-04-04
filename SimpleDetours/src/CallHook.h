#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class SIMPLEDETOURS_API CallHook : public HookBase
	{
	public:
		CallHook();
		CallHook(MultiPointer from, MultiPointer to);
		~CallHook();

		void initialize(MultiPointer from, MultiPointer to);
		void setupHook();
		void removeHook();
		dword version();
	private:
		MultiPointer place;
		MultiPointer target;
		byte originalCode[5];
	};
}
