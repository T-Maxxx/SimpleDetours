#include "JumpHook.h"
using namespace SimpleDetours;

SimpleDetours::JumpHook::JumpHook()
{
}

SimpleDetours::JumpHook::JumpHook(MultiPointer from, MultiPointer to)
{
}

SimpleDetours::JumpHook::~JumpHook()
{
}

void SimpleDetours::JumpHook::initialize(MultiPointer from, MultiPointer to)
{
}

void SimpleDetours::JumpHook::setupHook()
{
}

void SimpleDetours::JumpHook::removeHook()
{
}

dword SimpleDetours::JumpHook::version()
{
	return static_cast<dword>(JUMPHOOK_VERSION);
}
