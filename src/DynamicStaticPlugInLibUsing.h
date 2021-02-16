#ifndef DynamicStaticPlugInLibUsing_H
#define DynamicStaticPlugInLibUsing_H

#ifdef USE_DYNAMIC_LIB
#include "DynamicStaticPlugInLib.h"
#endif

#include <iostream>

namespace DynamicStaticPlugInLibUsing
{

	void example()
	{
#ifdef USE_DYNAMIC_LIB
		DynamicStaticPlugInLib::function();

		DynamicStaticPlugInLib::LibClass instnace;
		instnace.method();
#else
		std::cout << "DynamicStaticPlugInLib not linked !" << std::endl;
#endif
	}
}


#endif