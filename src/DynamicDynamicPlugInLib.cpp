#include "DynamicDynamicPlugInLib.h"

#include <iostream>


int WINAPI DllMain( HINSTANCE hInstance, DWORD fdReason, PVOID pvReserved )
{
	return TRUE;
}

DYNAMIC_LIB_API int CALLBACK function( char* str )
{
	std::cout << __FUNCTION__ << std::endl;

	return 0;
}