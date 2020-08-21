#include "StaticLib.h"

#include <iostream>

namespace StaticLib
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
