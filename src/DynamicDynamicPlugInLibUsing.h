#ifndef DynamicDynamicPlugInLibUsing_H
#define DynamicDynamicPlugInLibUsing_H

#include <iostream>

typedef int(WINAPI*functionPtr)(char*);

namespace DynamicDynamicPlugInLibUsing
{

	void example()
	{

		LPSTR libName = "dynamic_dynamic_plug_in_lib.dll";
		HINSTANCE plugInDll = ::LoadLibrary( libName );

		if ( plugInDll == NULL )
		{
			std::cout << "Can't load Library" << std::endl;
			return;
		}

		functionPtr libFunc = (functionPtr)::GetProcAddress(plugInDll, "function" );

		if ( libFunc == NULL )
		{
			std::cout << "Can't take library function address: error " << GetLastError() << std::endl;
		}
		else
		{
			libFunc( "string" );
		}

		::FreeLibrary(plugInDll);
	}
}

#endif