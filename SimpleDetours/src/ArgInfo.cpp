#include "ArgInfo.h"
using namespace SimpleDetours;
using namespace std;

SimpleDetours::ArgsInfo::ArgsInfo()
{
	args = NULL;
	argsCount = 0;
}

SimpleDetours::ArgsInfo::ArgsInfo(str argString) : ArgsInfo()
{
	parse(argString);
}

SimpleDetours::ArgsInfo::~ArgsInfo()
{
	if (argsCount)
		delete[] args;
}

void SimpleDetours::ArgsInfo::parse(str argString)
{
	string sArgs = argString;
	if (sArgs == "")
		return;

	argsCount = countBytes(sArgs, ',') + 1;
	args = new ArgInfo[argsCount];

	if (argsCount == 1) //sArgs looks like "eax+20"
		parseArgument(0, sArgs);
	else //sArgs is a complex: "eax,ebx+20,ecx"
	{
		string subArg;
		dword argNum = 0;
		dword start = 0;
		dword end = sArgs.find(',');
		while (end != string::npos)
		{
			subArg = sArgs.substr(start, end - start);
			parseArgument(argNum, subArg);
			++argNum;
			start = end + 1;
			end = sArgs.find(',', start);
		}
		//and last arg
		subArg = sArgs.substr(start);
		parseArgument(argNum, subArg);
	}
}

dword SimpleDetours::ArgsInfo::getArgumentsCount()
{
	return argsCount;
}

dword SimpleDetours::ArgsInfo::countBytes(std::string& str, byte b)
{
	dword count = 0;
	dword start = 0;
	dword end = str.find(b);
	while (end != string::npos)
	{
		++count;
		start = end + 1;
		end = str.find(b, start);
	}
	return count;
}

// num - index for arguments[num]
// arg - simple arg: e(a)x or e(a)x+20
void SimpleDetours::ArgsInfo::parseArgument(dword num, std::string & arg)
{
	// 1. is there an offset in arg?
	dword plusPos = arg.find('+');
	string substr;
	if (string::npos == plusPos || arg.find("stack", 0, 5))
	{ // Nope. So arg looks like e(a)x.
		substr = arg;
		args[num].regOffset = 0;
	}
	else
	{ // Yep. arg looks like e(a)x+22
		substr = arg.substr(0, plusPos);
		args[num].regOffset = atoi(arg.substr(plusPos + 1).c_str());
	}
	args[num].storingType = getStoringTypeForString(substr);
}

byte SimpleDetours::ArgsInfo::getStoringTypeForString(std::string& arg)
{
	if (arg == "eax")
		return AST_REG_EAX;
	else if (arg == "ecx")
		return AST_REG_ECX;
	else if (arg == "edx")
		return AST_REG_EDX;
	else if (arg == "ebx")
		return AST_REG_EBX;
	else if (arg == "esp")
		return AST_REG_ESP;
	else if (arg == "ebp")
		return AST_REG_EBP;
	else if (arg == "edi")
		return AST_REG_EDI;
	else if (arg == "esi")
		return AST_REG_ESI;
	else if (arg == "stack")
		return AST_STACK;

	return AST_ERROR;
}