#ifndef StaticLibUsing_H
#define StaticLibUsing_H


#include "StaticLib.h"

namespace StaticLibUsing
{

	void example()
	{
		StaticLib::function();

		StaticLib::LibClass instnace;
		instnace.method();
	}
}


#endif