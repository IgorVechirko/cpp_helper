#ifndef Templates_H
#define Templates_H

#include "CommonInclude.h"

namespace Templates
{
	//template< typename TypesPackage >
	void tempalteFunctionWithTypesPackage()
	{
		std::cout << "last function" << std::endl;
	}

	template< typename T, typename... TypesPackage >
	void tempalteFunctionWithTypesPackage(const T& firstArg, const TypesPackage&... argsPackage )
	{
		std::cout << "args count = " << sizeof...(TypesPackage) << std::endl;

		std::cout << firstArg << std::endl;
		tempalteFunctionWithTypesPackage( argsPackage... );
	}

	void example()
	{
		tempalteFunctionWithTypesPackage( "", 5, 0.054f, true );
		tempalteFunctionWithTypesPackage( 5, 0.054, true );
	}
	

	//template alias
	template< typename T>
	class MyAllocator
	{
	};

	template<typename T>
	using MyVec = std::vector<T,MyAllocator<T>>;

};

#endif