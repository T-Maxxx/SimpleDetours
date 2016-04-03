#include "ArgumentsInfo.h"
using namespace SimpleDetours;
using namespace std;

SimpleDetours::ArgumentsInfo::ArgumentsInfo()
{
	argumentsCount = 0;
	arguments = NULL;
}

SimpleDetours::ArgumentsInfo::~ArgumentsInfo()
{
	if (argumentsCount)
		delete[] arguments;
}
//TODO:
void SimpleDetours::ArgumentsInfo::parse(str args)
{
	string sArgs = args;
	if (sArgs == "")
	{
		argumentsCount = 0;
		return;
	}

	argumentsCount = countBytes(sArgs, ',') + 1;
	arguments = new Argument[argumentsCount];

	if (argumentsCount == 1) //sArgs looks like "eax+20"
	{
		parseArgument(0, sArgs);
	}
	else //sArgs is a complex: "eax,ebx+20,ecx"
	{
		string subArg;
		dword argNum = argumentsCount - 1;
		dword start = 0;
		dword end = sArgs.find(',');
		while (end != string::npos)
		{
			subArg = sArgs.substr(start, end - start);
			parseArgument(argNum, subArg);
			--argNum;
			start = end + 1;
			end = sArgs.find(',', start);
		}
		//and last arg
		subArg = sArgs.substr(start);
		parseArgument(argNum, subArg);
	}
}

byte* SimpleDetours::ArgumentsInfo::getRawCode(dword num)
{
	if (num >= argumentsCount)
		return NULL;
	return arguments[num].rawCode;
}

dword SimpleDetours::ArgumentsInfo::getRawCodeSize(dword num)
{
	if (num >= argumentsCount)
		return 0;
	return arguments[num].rawCodeSize;
}

dword SimpleDetours::ArgumentsInfo::getTotalSize()
{
	dword result = 0;
	for (dword i = 0; i < argumentsCount; ++i)
		result += arguments[i].rawCodeSize;
	return result;
}

dword SimpleDetours::ArgumentsInfo::getArgumentsCount()
{
	return argumentsCount;
}

dword SimpleDetours::ArgumentsInfo::countBytes(std::string& str, byte b)
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

/// num - index for arguments[num]
/// arg - simple arg: e(a)x or e(a)x+20
void SimpleDetours::ArgumentsInfo::parseArgument(dword num, std::string & arg)
{
	// 1. is there an offset in arg?
	dword plusPos = arg.find('+');
	if (string::npos == plusPos)
	{ // Nope. So arg looks like e(a)x. All we need is to push correct register.
		arguments[num].rawCodeSize = 1;
		arguments[num].rawCode[0] = getPushOpcodeForRegister(arg);		
	}
	else
	{ // Yep. arg looks like e(a)x+22
		string reg = arg.substr(0, plusPos);
		dword offset = atoi(arg.substr(plusPos + 1).c_str());		
		arguments[num].rawCodeSize = 7;

		MultiPointer p = arguments[num].rawCode;

		p.bp()[0] = OP_ADD_R32_M32;
		p.bp()[1] = getAddOpcodeForRegister(reg);
		(p + 2).dp()[0] = offset;
		p.bp()[6] = getPushOpcodeForRegister(reg);
	}
}

byte SimpleDetours::ArgumentsInfo::getPushOpcodeForRegister(std::string & arg)
{
	if (arg == "eax")
		return OP_PUSH_EAX;
	else if (arg == "ecx")
		return OP_PUSH_ECX;
	else if (arg == "edx")
		return OP_PUSH_EDX;
	else if (arg == "ebx")
		return OP_PUSH_EBX;
	else if (arg == "esp")
		return OP_PUSH_ESP;
	else if (arg == "ebp")
		return OP_PUSH_EBP;
	else if (arg == "edi")
		return OP_PUSH_EDI;
	else if (arg == "esi")
		return OP_PUSH_ESI;

	return OP_NOP;
}

byte SimpleDetours::ArgumentsInfo::getAddOpcodeForRegister(std::string & arg)
{
	if (arg == "eax")
		return OP_ADD_R32_EAX;
	else if (arg == "ecx")
		return OP_ADD_R32_ECX;
	else if (arg == "edx")
		return OP_ADD_R32_EDX;
	else if (arg == "ebx")
		return OP_ADD_R32_EBX;
	else if (arg == "esp")
		return OP_ADD_R32_ESP;
	else if (arg == "ebp")
		return OP_ADD_R32_EBP;
	else if (arg == "edi")
		return OP_ADD_R32_EDI;
	else if (arg == "esi")
		return OP_ADD_R32_ESI;

	return OP_NOP;
}
