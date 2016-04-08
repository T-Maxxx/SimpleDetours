#pragma once
#include "MultiPointer.h"
#include "ArgsInfo.h"

#define VariadicFunction( name, address, returnType, ... ) \
	{returnType(*name)(__VA_ARGS__, ...) = (returnType(*)(__VA_ARGS__, ...))address;}

namespace SimpleDetours
{
	template<typename RetType, typename ... Args>
	class Function
	{
	public:
		Function();
		Function(MultiPointer address, ArgumentStoringType retRegister, str argsStr);
		~Function();
		
		void initialize(MultiPointer address, ArgumentStoringType retRegister, str argsStr);
		R operator()(A... args);
	private:
		MultiPointer function;
		MultiPointer rawCode;
		dword rawCodeSize;
		str args;
		byte retReg;
		R callResult;
		bool isInitialized;
	};

	template<typename R, typename ... A>
	Function<R, A...>::Function()
	{
		function = NULL;
		rawCode = NULL;
		rawCodeSize = 0;
		args = NULL;
		byte retReg = AST_ERROR;
		isInitialized = false;
	}

	template<typename R, typename ... A>
	Function<R, A...>::Function(MultiPointer address, ArgumentStoringType retRegister, str argsStr) : Function()
	{
		initialize(address, retRegister, argumentsInfo);
	}

	template<typename R, typename ... A>
	Function<R, A...>::~Function()
	{
		if(rawCodeSize)
			VirtualFree(rawCode.vp, rawCodeSize, MEM_RELEASE); //TODO: check flag
	}

	template<typename R, typename ...A>
	void Function<R, A...>::initialize(MultiPointer address, ArgumentStoringType retRegister, str argsStr);
	{
		function = address;
		args = argsStr;
		retReg = retRegister == AST_STACK ? AST_ERROR : retRegister;
		isInitialized = true;
	}

	template<typename R, typename ...A>
	R Function<R, A...>::operator()(A ...varargs)
	{
		ArgsInfo a(args);
		//push anything + call function + add esp if pushed + push result + push retaddr and ret
		//rawCodeSize = 
		//TODO
		_asm
		{ 
			call rawCode;
			///???
		}
		
		return callResult;
	}
}
