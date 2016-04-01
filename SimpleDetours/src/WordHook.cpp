#include "WordHook.h"
using namespace SimpleDetours;

SimpleDetours::WordHook::WordHook()
{
	place = NULL;
	original = 0x0000;
	replace = 0x0000;
}

SimpleDetours::WordHook::WordHook(MultiPointer to, word w) : WordHook()
{
	initialize(to, w);
	setupHook();
}

SimpleDetours::WordHook::~WordHook()
{
	removeHook();
}

void SimpleDetours::WordHook::initialize(MultiPointer to, word w)
{
	if (isInitialized)
		return;
	
	place = to;
	original = *(place.wp());
	replace = w;

	isInitialized = true;
}

void SimpleDetours::WordHook::setupHook()
{
	if(isDeployed || !isInitialized)
		return;
	
	setWord(place, replace);
	isDeployed = true;
}

void SimpleDetours::WordHook::removeHook()
{
	if(!isDeployed || !isInitialized)
		return;
		
	setWord(place, original);
	isDeployed = false;
}

dword SimpleDetours::WordHook::version()
{
	return static_cast<dword>(WORDHOOK_VERSION);
}
