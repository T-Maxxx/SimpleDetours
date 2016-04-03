#include "HookBase.h"
using namespace SimpleDetours;

SimpleDetours::HookBase::HookBase()
{
	isDeployed = false;
	isInitialized = false;
}

dword SimpleDetours::HookBase::protectAddress(MultiPointer address, dword size, dword flags)
{
	dword oldFlags = NULL;
	dword result = VirtualProtect(address.vp(), size, flags, &oldFlags);
	if (result == 0)
		ExitProcess(1);

	return oldFlags;
}

SimpleDetours::byte SimpleDetours::HookBase::setByte(MultiPointer address, byte b)
{
	dword oldFlags = protectAddress(address, sizeof(byte), PAGE_EXECUTE_READWRITE);
	byte oldByte = putByte(address, b);
	protectAddress(address, sizeof(byte), oldFlags);
	return oldByte;
}

word SimpleDetours::HookBase::setWord(MultiPointer address, word w)
{
	dword oldFlags = protectAddress(address, sizeof(word), PAGE_EXECUTE_READWRITE);
	word oldWord = putWord(address, w);
	protectAddress(address, sizeof(word), oldFlags);
	return oldWord;
}

dword SimpleDetours::HookBase::setDword(MultiPointer address, dword d)
{
	dword oldFlags = protectAddress(address, sizeof(dword), PAGE_EXECUTE_READWRITE);
	dword oldDword = putDword(address, d);
	protectAddress(address, sizeof(dword), oldFlags);
	return oldDword;
}

void SimpleDetours::HookBase::setMemory(MultiPointer to, MultiPointer from, dword size)
{
	dword oldFlags = protectAddress(to, size, PAGE_EXECUTE_READWRITE);
	putMemory(to, from, size);
	protectAddress(to, size, oldFlags);
}

void SimpleDetours::HookBase::setBytes(MultiPointer to, dword count, byte b)
{
	dword oldFlags = protectAddress(to, count, PAGE_EXECUTE_READWRITE);
	putBytes(to, count, b);
	protectAddress(to, count, oldFlags);
}

inline SimpleDetours::byte SimpleDetours::HookBase::putByte(MultiPointer address, SimpleDetours::byte b)
{
	byte oldByte = *(address.bp());
	*(address.bp()) = b;
	return oldByte;
}
inline word SimpleDetours::HookBase::putWord(MultiPointer address, word w)
{
	word oldWord = *(address.wp());
	*(address.wp()) = w;
	return oldWord;
}
inline dword SimpleDetours::HookBase::putDword(MultiPointer address, dword d)
{
	dword oldDword = *(address.dp());
	*(address.dp()) = d;
	return oldDword;
}

void SimpleDetours::HookBase::putMemory(MultiPointer to, MultiPointer from, dword size)
{
	memcpy_s(to.vp(), size, from.vp(), size);
}

void SimpleDetours::HookBase::putBytes(MultiPointer to, dword count, byte b)
{
	memset(to.vp(), b, count);
}
