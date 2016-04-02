#pragma once
#include "MultiPointer.h"

namespace SimpleDetours
{
	class ArgumentsInfo
	{
	public:
		ArgumentsCount();
		~ArgumentsCount();
		void addRecord(dword type, )
		
		dword recordCount;
	};
	
	template<class R, class... A>
	class SIMPLEDETOURS_API Function
	{
	public:
		Function();
		~Function();
		
		void initialize(MultiPointer address, ArgumentsInfo* args);
		R call(A... args);
		R operator()(const A... args);
	private:
		R (*function)(A...);
		dword argsCount;
		MultiPointer rawCode;
		dword rawCodeSize;
		
		void recursiveFillRawCode();
	};
}
