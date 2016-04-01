#include "ByteHook.h"
using namespace SimpleDetours;

SimpleDetours::ByteHook::ByteHook()
{
	place = NULL;
	original = 0;
	replace = 0;
}

SimpleDetours::ByteHook::ByteHook(MultiPointer to, byte b) : ByteHook()
{
	initialize(to, b);
	setupHook();
}

SimpleDetours::ByteHook::~ByteHook()
{
	removeHook();
}

void SimpleDetours::ByteHook::initialize(MultiPointer to, byte b)
{
	if (isInitialized)
		return;

	place = to;
	original = *(place.bp());
	replace = b;

	isInitialized = true;
}

void SimpleDetours::ByteHook::setupHook()
{
	if(isDeployed || !isInitialized)
		return;
		
	setByte(place, replace);
	isDeployed = true;
}

void SimpleDetours::ByteHook::removeHook()
{
	if(!isDeployed || !isInitialized)
		return;
		
	setByte(place, original);
	isDeployed = false;
}

dword SimpleDetours::ByteHook::version()
{
	return static_cast<dword>(BYTEHOOK_VERSION);
}
