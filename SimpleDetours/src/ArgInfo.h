#pragma once
#include "MultiPointer.h"
#include <string>

namespace SimpleDetours
{
	enum ArgumentStoringType
	{
		AST_REG_EAX,
		AST_REG_ECX,
		AST_REG_EDX,
		AST_REG_EBX,
		AST_REG_ESP,
		AST_REG_EBP,
		AST_REG_EDI,
		AST_REG_ESI,
		AST_STACK,
		AST_ERROR
	};
	
	class ArgsInfo
	{
	public:
		ArgsInfo();
		ArgsInfo(str argString);
		~ArgsInfo();

		void parse(str argString);
		dword getArgumentsCount();

	private:
		struct ArgInfo;
		ArgInfo* args;
		dword argsCount;

		dword countBytes(std::string& str, byte b);
		void parseArgument(dword num, std::string& arg);
		byte getStoringTypeForString(std::string& arg);
	};

	struct ArgsInfo::ArgInfo
	{
		byte storingType;
		int regOffset;
	};
}
