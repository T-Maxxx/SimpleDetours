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
	place = to;
	original = *(place.bp());
	replace = b;
}

SimpleDetours::ByteHook::~ByteHook()
{
	removeHook();
}

void SimpleDetours::ByteHook::setupHook()
{
	if(isDeployed)
		return;
		
	setByte(place, replace);
	isDeployed = true;
}

void SimpleDetours::ByteHook::removeHook()
{
	if(!isDeployed)
		return;
		
	setByte(place, original);
	isDeployed = false;
}

dword SimpleDetours::ByteHook::version()
{
	return static_cast<dword>(BYTEHOOK_VERSION);
}

