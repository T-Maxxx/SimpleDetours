#include "NopHook.hpp"
using namespace SimpleDetours;

SimpleDetours::NopHook::NopHook()
{
	place = NULL;
	originalBytes = NULL;
	originalBytesSize = 0;
}

SimpleDetours::NopHook::NopHook(MultiPointer target, dword size) : NopHook()
{
	initialize(target, size);
	setupHook();
}

SimpleDetours::NopHook::~NopHook()
{
	removeHook();
	if(originalBytesSize)
		delete[] originalBytes.vp();
}

void SimpleDetours::NopHook::initialize(MultiPointer target, dword size)
{
	if(isInitialized)
		return;
	
	place = target;
	originalBytesSize = size;
	originalBytes = new byte[size];
	putMemory(originalBytes, place, size);
	
	isInitialized = true;
}

void SimpleDetours::NopHook::setupHook()
{
	if(!isInitialized || isDeployed)
		return;
	
	MultiPointer nops = new byte[originalBytesSize];
	memset(nops.vp(), OP_NOP, originalBytesSize);
	setMemory(place, nops, originalBytesSize);
	delete[] nops.vp();
	isDeployed = true;
}

void SimpleDetours::NopHook::removeHook()
{
	if(!isInitialized || !isDeployed)
		return;
		
	setMemory(place, originalBytes, originalbytesSize);
	isDeployed = false;
}
