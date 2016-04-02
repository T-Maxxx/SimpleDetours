#pragma once
#define DETOUR_VERSION 1
#define MEMORYHOOK_VERSION 1
#define BYTEHOOK_VERSION 1
#define WORDHOOK_VERSION 1
#define DWORDHOOK_VERSION 1

#ifdef SIMPLEDETOURS_DLL
#define SIMPLEDETOURS_API _declspec(dllimport)
#else
#define SIMPLEDETOURS_API _declspec(dllexport)
#endif

namespace SimpleDetours
{
	typedef unsigned char      byte;
	typedef unsigned short int word;
	typedef unsigned long int  dword;
	typedef void*              ptr;
}