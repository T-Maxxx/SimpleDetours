#pragma once
#include "MultiPointer.h"

namespace SimpleDetours
{
	template<typename T>
	T GlobalVariable(dword address)
	{
		return reinterpret_cast<T>(address);
	}
}