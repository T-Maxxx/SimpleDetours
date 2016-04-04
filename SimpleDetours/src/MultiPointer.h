#pragma once
#include "Declarations.h"

namespace SimpleDetours
{
	class SIMPLEDETOURS_API MultiPointer
	{
	public:
		MultiPointer();
		MultiPointer(dword   d);
		MultiPointer(int     i);
		MultiPointer(ptr     p);
		MultiPointer(byte*  bp);
		MultiPointer(word*  wp);
		MultiPointer(dword* dp);
		MultiPointer(char*  s);

		dword   d();
		ptr    vp();
		byte*  bp();
		word*  wp();
		dword* dp();
		char*   s();

		MultiPointer operator+(const dword& rv);
		MultiPointer operator+(MultiPointer& rv);
		MultiPointer operator-(const dword& rv);
		MultiPointer operator-(MultiPointer& rv);

	private:
		dword pointer;
	};
}
