#ifndef StaticLibUsing_H
#define StaticLibUsing_H

#ifdef USE_STATIC_LIB
#include "StaticLib.h"
#endif

namespace StaticLibUsing
{

	void example()
	{
#ifdef USE_STATIC_LIB
		StaticLib::function();

		StaticLib::LibClass instnace;
		instnace.method();
#else
		std::cout << "StaticLib not linked !" << std::endl;
#endif
	}
}


#endif