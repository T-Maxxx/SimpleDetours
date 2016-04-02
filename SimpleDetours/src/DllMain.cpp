#include <Windows.h>
#define SIMPLEDETOURS_DLL true
#include "Declarations.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH :
	case DLL_PROCESS_DETACH : 
	case DLL_THREAD_ATTACH :
	case DLL_THREAD_DETACH :
		break;
	}
	
	return TRUE;
}
