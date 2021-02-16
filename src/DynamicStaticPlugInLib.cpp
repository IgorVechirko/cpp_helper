#include "DynamicStaticPlugInLib.h"

#include <iostream>


int WINAPI DllMain( HINSTANCE hInstance, DWORD fdReason, PVOID pvReserved )
{
	return TRUE;
}


namespace DynamicStaticPlugInLib
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