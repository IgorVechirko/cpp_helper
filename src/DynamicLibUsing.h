#ifndef DynamicLibUsing_H
#define DynamicLibUsing_H


#include "DynamicLib.h"

namespace DynamicLibUsing
{

	void example()
	{
		DynamicLib::function();

		DynamicLib::LibClass instnace;
		instnace.method();
	}
}


#endif