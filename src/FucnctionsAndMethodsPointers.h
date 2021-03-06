#ifndef FucnctionsAndMethodsPointers_H
#define FucnctionsAndMethodsPointers_H

#include "CommonInclude.h"
#include <functional>

namespace FucnctionsAndMethodsPointers
{
	struct returnType
	{
		int integer = 0;
		char symb = 0;
	};

	returnType function( int arg1, float arg2, const returnType& arg3 )
	{
		std::cout<< __FUNCTION__ << std::endl;

		returnType result;
		return result;
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
		{
			returnType(*functionPtr)(int,float,const returnType&) = &function;
			functionPtr( 5, 0.2f, returnType() );

			TestClass instance;
			returnType(TestClass::*methodPtr)(long,returnType*) = &TestClass::method;
			returnType arg2;
			(instance.*methodPtr)( 5l, &arg2 );
		}

		std::cout << std::endl;

		{
			std::function<returnType(int,float,const returnType&)> funcFunctor( function );
			funcFunctor(5, 0.3f, returnType() );

			TestClass instance;
			std::_Binder< std::_Unforced, returnType(TestClass::*)(long,returnType*), TestClass*, long, const std::_Ph<1>& >  methodFunctor = std::bind( &TestClass::method, &instance, 5l, std::placeholders::_1 );
			returnType arg2;
			methodFunctor( &arg2 );
		}
	}
};

#endif