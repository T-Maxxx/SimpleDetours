#include "CallHook.h"
using namespace SimpleDetours;

SimpleDetours::CallHook::CallHook()
{
	place = NULL;
	target = NULL;
}

SimpleDetours::CallHook::CallHook(MultiPointer from, MultiPointer to) : CallHook()
{
	initialize(from, to);
	setupHook();
}

SimpleDetours::CallHook::~CallHook()
{
	removeHook();
}

void SimpleDetours::CallHook::initialize(MultiPointer from, MultiPointer to)
{
	if (isInitialized)
		return;

	place = from;
	target = to;
	putMemory(originalCode, place, 5);
	isInitialized = true;
}

void SimpleDetours::CallHook::setupHook()
{
	if (isDeployed || !isInitialized)
		return;

	setByte(place, OP_CALL);
	setDword(place + 1, (target - place - 5).d());

	isDeployed = true;
}

void SimpleDetours::CallHook::removeHook()
{
	if (!isDeployed || !isInitialized)
		return;

	setMemory(place, originalCode, 5);

	isDeployed = false;
}

dword SimpleDetours::CallHook::version()
{
	return static_cast<dword>(JUMPHOOK_VERSION);
}
