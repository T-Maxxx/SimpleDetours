#pragma once
#include "MultiPointer.h"
#include "ArgInfo.h"

#define VariadicFunction( name, address, returnType, ... ) \
	{returnType(*name)(__VA_ARGS__, ...) = (returnType(*)(__VA_ARGS__, ...))address}

namespace SimpleDetours
{
	template<typename RetType, typename ... Args>
	class Function
	{
	public:
		Function();
		Function(MultiPointer address, str argumentsInfo);
		~Function();
		
		void initialize(MultiPointer address, str argumentsInfo);
		R call(A... args);
		R operator()(A... args);
	private:
		MultiPointer function;
		MultiPointer rawCode;
		dword rawCodeSize;
		ArgsInfo args;
	};

	template<typename R, typename ... A>
	Function<R, A...>::Function()
	{
	/*	function = NULL;
		rawCode = NULL;
		rawCodeSize = 0;
		isInitialized = false;*/
	}

	template<typename R, typename ... A>
	Function<R, A...>::Function(MultiPointer address, int argumentsInfo) : Function()
	{
	//	initialize(address);
	}

	template<typename R, typename ... A>
	Function<R, A...>::~Function()
	{
	/*	if (rawCode)
			VirtualFree(rawCode.vp(), rawCodeSize, MEM_RELEASE);*/
	}

	template<typename R, typename ...A>
	void Function<R, A...>::initialize(MultiPointer address)
	{
	/*	function = address;
		isInitialized = true;*/
	}

	template<typename R, typename ...A>
	R Function<R, A...>::call(A ...args)
	{
	//	return function(A...);
	}

	template<typename R, typename ...A>
	R Function<R, A...>::operator()(A ...args)
	{
	//	return call(A...);
	}
}
