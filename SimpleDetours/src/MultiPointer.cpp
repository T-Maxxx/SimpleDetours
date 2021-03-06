#include "MultiPointer.h"
using namespace SimpleDetours;

SimpleDetours::MultiPointer::MultiPointer()
{
	pointer = 0;
}

SimpleDetours::MultiPointer::MultiPointer(dword d)
{
	pointer = d;
}

SimpleDetours::MultiPointer::MultiPointer(int i)
{
	pointer = i;
}

SimpleDetours::MultiPointer::MultiPointer(ptr p)
{
	pointer = reinterpret_cast<dword>(p);
}

SimpleDetours::MultiPointer::MultiPointer(byte* bp)
{
	pointer = reinterpret_cast<dword>(bp);
}

SimpleDetours::MultiPointer::MultiPointer(word* wp)
{
	pointer = reinterpret_cast<dword>(wp);
}

SimpleDetours::MultiPointer::MultiPointer(dword* dp)
{
	pointer = reinterpret_cast<dword>(dp);
}

SimpleDetours::MultiPointer::MultiPointer(char* s)
{
	pointer = reinterpret_cast<dword>(s);
}

dword SimpleDetours::MultiPointer::d()
{
	return pointer;
}

ptr SimpleDetours::MultiPointer::vp()
{
	return reinterpret_cast<ptr>(pointer);
}

byte* SimpleDetours::MultiPointer::bp()
{
	return reinterpret_cast<byte*>(pointer);
}

word* SimpleDetours::MultiPointer::wp()
{
	return reinterpret_cast<word*>(pointer);
}

dword* SimpleDetours::MultiPointer::dp()
{
	return reinterpret_cast<dword*>(pointer);
}

char* SimpleDetours::MultiPointer::s()
{
	return reinterpret_cast<char*>(pointer);
}

SimpleDetours::MultiPointer SimpleDetours::MultiPointer::operator-(const dword& rv)
{
	return MultiPointer(d() - rv);
}

SimpleDetours::MultiPointer SimpleDetours::MultiPointer::operator-(MultiPointer& rv)
{
	return MultiPointer(pointer - rv.d());
}

SimpleDetours::MultiPointer SimpleDetours::MultiPointer::operator+(const dword& rv)
{
	return MultiPointer(d() + rv);
}

SimpleDetours::MultiPointer SimpleDetours::MultiPointer::operator+(MultiPointer& rv)
{
	return MultiPointer(pointer + rv.d());
}
