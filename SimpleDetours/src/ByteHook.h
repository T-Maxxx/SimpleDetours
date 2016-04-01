#pragma once
#include "HookBase.h"

namespace SimpleDetours
{
	class ByteHook : public HookBase
	{
	public:
		ByteHook();
		ByteHook(MultiPointer to, byte b);
		~ByteHook();
		
		void initialize(MultiPointer to, byte b);
		void setupHook();
		void removeHook();
		dword version();
	private:
		MultiPointer place;
		byte replace;
		byte original;
	};
}