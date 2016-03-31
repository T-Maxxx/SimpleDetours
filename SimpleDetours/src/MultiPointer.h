#pragma once
#include "Declarations.h"

namespace SimpleDetours
{
	class MultiPointer
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

		inline dword   d();
		inline ptr    vp();
		inline byte*  bp();
		inline word*  wp();
		inline dword* dp();
		inline char*   s();

		MultiPointer operator+(const dword& rv);
		MultiPointer operator-(MultiPointer& rv);

	private:
		dword pointer;
	};
}
