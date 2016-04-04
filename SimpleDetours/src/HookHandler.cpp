#include "HookHandler.h"

using namespace std;
using namespace SimpleDetours;

SimpleDetours::HookHandler::HookHandler()
{
	stByteHooks = new stack<ByteHook*>();
	stWordHooks = new stack<WordHook*>();
	stDwordHooks = new stack<DwordHook*>();
	stMemoryHooks = new stack<MemoryHook*>();
	stDetours = new stack<Detour*>();
	stJumpHooks = new stack<JumpHook*>();
	stCallHooks = new stack<CallHook*>();
}

SimpleDetours::HookHandler::~HookHandler()
{
	while (!stByteHooks->empty())
	{
		delete stByteHooks->top();
		stByteHooks->pop();
	}
	delete stByteHooks;

	while (!stWordHooks->empty())
	{
		delete stWordHooks->top();
		stWordHooks->pop();
	}
	delete stWordHooks;

	while (!stDwordHooks->empty())
	{
		delete stDwordHooks->top();
		stDwordHooks->pop();
	}
	delete stDwordHooks;

	while (!stMemoryHooks->empty())
	{
		delete stMemoryHooks->top();
		stMemoryHooks->pop();
	}
	delete stMemoryHooks;

	while (!stDetours->empty())
	{
		delete stDetours->top();
		stDetours->pop();
	}
	delete stDetours;

	while (!stJumpHooks->empty())
	{
		delete stJumpHooks->top();
		stJumpHooks->pop();
	}
	delete stJumpHooks;

	while (!stCallHooks->empty())
	{
		delete stCallHooks->top();
		stCallHooks->pop();
	}
	delete stCallHooks;
}

void SimpleDetours::HookHandler::addByteHook(MultiPointer place, byte b)
{
	stByteHooks->push(new ByteHook(place, b));
}

void SimpleDetours::HookHandler::addWordHook(MultiPointer place, word w)
{
	stWordHooks->push(new WordHook(place, w));
}

void SimpleDetours::HookHandler::addDwordHook(MultiPointer place, dword d)
{
	stDwordHooks->push(new DwordHook(place, d));
}

void SimpleDetours::HookHandler::addMemoryHook(MultiPointer place, MultiPointer memory, dword memSize)
{
	stMemoryHooks->push(new MemoryHook(place, memory, memSize));
}

void SimpleDetours::HookHandler::addDetour(MultiPointer place, MultiPointer retAddr, MultiPointer detour, str args)
{
	stDetours->push(new Detour(place, retAddr, detour, args));
}

void SimpleDetours::HookHandler::addJumpHook(MultiPointer place, MultiPointer target)
{
	stJumpHooks->push(new JumpHook(place, target));
}

void SimpleDetours::HookHandler::addCallHook(MultiPointer place, MultiPointer target)
{
	stCallHooks->push(new CallHook(place, target));
}
