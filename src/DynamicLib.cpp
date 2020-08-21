#include "DynamicLib.h"

#include <iostream>

namespace DynamicLib
{
	void function()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	void LibClass::method()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

}