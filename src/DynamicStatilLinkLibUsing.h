#ifndef DynamicLibUsing_H
#define DynamicLibUsing_H

#ifdef USE_DYNAMIC_LIB
#include "DynamicLib.h"
#endif

#include <iostream>

namespace DynamicLibUsing
{

	void example()
	{
#ifdef USE_DYNAMIC_LIB
		DynamicLib::function();

		DynamicLib::LibClass instnace;
		instnace.method();
#else
		std::cout << "DynamicLib not linked !" << std::endl;
#endif
	}
}


#endif