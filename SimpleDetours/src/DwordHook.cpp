#include "DwordHook.h"
using namespace SimpleDetours;

SimpleDetours::DwordHook::DwordHook()
{
	place = NULL;
	original = 0x00000000;
	replace = 0x00000000;
}

SimpleDetours::DwordHook::DwordHook(MultiPointer to, dword d) : DwordHook()
{
	place = to;
	original = *(place.dp());
	replace = d;
	
	setupHook();
}

SimpleDetours::DwordHook::~DwordHook()
{
	removeHook();
}

void SimpleDetours::DwordHook::setupHook()
{
	if(isDeployed)
		return;
		
	setDword(place, replace);
	isDeployed = true;
}

void SimpleDetours::DwordHook::removeHook()
{
	if(!isDeployed)
		return;
		
		setDword(place, original);
		isDeployed = false;
}

dword SimpleDetours::DwordHook::version()
{
	return static_cast<dword>(DWORDHOOK_VERSION);
}
