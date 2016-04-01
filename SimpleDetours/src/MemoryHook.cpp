#include "MemoryHook.h"
using namespace SimpleDetours;

SimpleDetours::MemoryHook::MemoryHook()
{
	originalBytes = NULL;
	originalBytesSize = 0;
	place = NULL;
	memory = NULL;
	memorySize = 0;
}

SimpleDetours::MemoryHook::MemoryHook(MultiPointer to, MultiPointer from, dword size) : MemoryHook()
{
	initialize(to, from, size);
	setupHook();
}

SimpleDetours::MemoryHook::~MemoryHook()
{
	removeHook();
	delete[] memory.vp();
	delete[] originalBytes.vp();
}

void SimpleDetours::MemoryHook::initialize(MultiPointer to, MultiPointer from, dword size)
{
	if (isInitialized)
		return;

	place = to;

	memorySize = size;
	memory = new byte[size]();
	putMemory(memory, from, size);

	originalBytesSize = size;
	originalBytes = new byte[size]();
	putMemory(originalBytes, place, originalBytesSize);

	isInitialized = true;
}

void SimpleDetours::MemoryHook::setupHook()
{
	if(isDeployed || !isInitialized)
		return;
	
	setMemory(place, memory, memorySize);
	isDeployed = true;
}

void SimpleDetours::MemoryHook::removeHook()
{
	if(!isDeployed || !isInitialized)
		return;
		
	setMemory(place, originalBytes, originalBytesSize);
	isDeployed = false;
}

dword SimpleDetours::MemoryHook::version()
{
	return static_cast<dword>(MEMORYHOOK_VERSION);
}
