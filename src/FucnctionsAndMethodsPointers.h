#ifndef FucnctionsAndMethodsPointers_H
#define FucnctionsAndMethodsPointers_H

#include "CommonInclude.h"

namespace FucnctionsAndMethodsPointers
{
	struct returnType
	{
		int integer;
		char symb;
	};

	returnType function( int arg1, float arg2, const returnType& arg3 )
	{
		std::cout<< __FUNCTION__ << std::endl;

		return returnType();
	}

	class TestClass
	{
		public:	

			returnType method( long arg1, returnType* arg2 )
			{
				std::cout << __FUNCTION__ << std::endl;

				return returnType();
			}
	};


	void example()
	{
		returnType(*functionPtr)(int,float,const returnType&) = &function;
		functionPtr( 5, 0.2f, returnType() );

		TestClass instance;
		returnType(TestClass::*methodPtr)(long,returnType*) = &TestClass::method;
		returnType arg2;
		(instance.*methodPtr)( 5, &arg2 );
	}
};

#endif