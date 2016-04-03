#pragma once
#include "MultiPointer.h"
#include <string>

using namespace std;

#ifndef NULL
#define NULL (0)
#endif

namespace SimpleDetours
{
	class SIMPLEDETOURS_API ArgumentsInfo
	{
	public:
		ArgumentsInfo();
		~ArgumentsInfo();

		void parse(str args);
		byte* getRawCode(dword num);
		dword getRawCodeSize(dword num);
		dword getTotalSize();
		dword getArgumentsCount();

	private:
		struct Argument;
		Argument* arguments;
		dword argumentsCount;

		dword countBytes(std::string& str, byte b);
		void parseArgument(dword num, std::string& arg);
		byte getPushOpcodeForRegister(std::string& arg);
		byte getAddOpcodeForRegister(std::string& arg);
	};

	struct ArgumentsInfo::Argument
	{
		byte rawCode[7]; //<= 7
		dword rawCodeSize;
	};
}
