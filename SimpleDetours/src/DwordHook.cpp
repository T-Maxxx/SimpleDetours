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
	initialize(to, d);
	setupHook();
}

SimpleDetours::DwordHook::~DwordHook()
{
	removeHook();
}

void SimpleDetours::DwordHook::initialize(MultiPointer to, dword d)
{
	if (isInitialized)
		return;

	place = to;
	original = *(place.dp());
	replace = d;
	isInitialized = true;
}

void SimpleDetours::DwordHook::setupHook()
{
	if(isDeployed || !isInitialized)
		return;
		
	setDword(place, replace);
	isDeployed = true;
}

void SimpleDetours::DwordHook::removeHook()
{
	if(!isDeployed || !isInitialized)
		return;
		
	setDword(place, original);
	isDeployed = false;
}

dword SimpleDetours::DwordHook::version()
{
	return static_cast<dword>(DWORDHOOK_VERSION);
}
