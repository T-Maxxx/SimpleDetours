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
	place = to;
	memory = new byte[size]();
	memorySize = size;
	putMemory(memory, from, size);
	
	setupHook();
}

SimpleDetours::MemoryHook::~MemoryHook()
{
	removeHook();
	delete[] memory;
}

SimpleDetours::MemoryHook::setupHook()
{
	if(isDeployed)
		return;
		
	originalBytesSize = memorySize;
	originalBytes = new byte[originalBytesSize]();
	putMemory(originalBytes, place, originalBytesSize);
	setMemory(place, memory, memorySize);
	isDeployed = true;
}

SimpleDetours::MemoryHook::removeHook()
{
	if(!isDeployed)
		return;
		
	setMemory(place, originalBytes, originalBytesSize);
	delete[] originalBytes;
	originalBytesSize = 0;
	isDeployed = false;
}

SimpleDetours::MemoryHook::version()
{
	return static_cast<dword>(MEMORYHOOK_VERSION);
}
