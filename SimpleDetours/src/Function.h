#pragma once
#include "MultiPointer.h"

namespace SimpleDetours
{
	template<typename R, typename ... A>
	class Function
	{
	public:
		Function();
		Function(MultiPointer address);
		~Function();
		
		void initialize(MultiPointer address);
		R call(A... args);
		R operator()(const A... args);
	private:
		R (*function)(A...);
		MultiPointer rawCode;
		dword rawCodeSize;
		bool isInitialized;
	};

	template<typename R, typename ... A>
	Function<R, A...>::Function()
	{
		function = NULL;
		rawCode = NULL;
		rawCodeSize = 0;
		isInitialized = false;
	}

	template<typename R, typename ... A>
	Function<R, A...>::Function(MultiPointer address) : Function()
	{
		initialize(address);
	}

	template<typename R, typename ... A>
	Function<R, A...>::~Function()
	{
		if (rawCode)
			VirtualFree(rawCode.vp(), rawCodeSize, MEM_RELEASE);
	}

	template<typename R, typename ...A>
	void Function<R, A...>::initialize(MultiPointer address)
	{
		function = address;
		isInitialized = true;
	}

	template<typename R, typename ...A>
	R Function<R, A...>::call(A ...args)
	{
		return function(A...);
	}

	template<typename R, typename ...A>
	R Function<R, A...>::operator()(const A ...args)
	{
		return call(A...);
	}
}
