#include "JumpHook.h"
using namespace SimpleDetours;

SimpleDetours::JumpHook::JumpHook()
{
	place = NULL;
	target = NULL;
}

SimpleDetours::JumpHook::JumpHook(MultiPointer from, MultiPointer to) : JumpHook()
{
	initialize(from, to);
	setupHook();
}

SimpleDetours::JumpHook::~JumpHook()
{
	removeHook();
}

void SimpleDetours::JumpHook::initialize(MultiPointer from, MultiPointer to)
{
	if (isInitialized)
		return;

	place = from;
	target = to;
	putMemory(originalCode, place, 5);
	isInitialized = true;
}

void SimpleDetours::JumpHook::setupHook()
{
	if (isDeployed || !isInitialized)
		return;

	setByte(place, OP_JMP);
	setDword(place + 1, (target - place - 5).d());

	isDeployed = true;
}

void SimpleDetours::JumpHook::removeHook()
{
	if (!isDeployed || !isInitialized)
		return;

	setMemory(place, originalCode, 5);

	isDeployed = false;
}

dword SimpleDetours::JumpHook::version()
{
	return static_cast<dword>(JUMPHOOK_VERSION);
}
