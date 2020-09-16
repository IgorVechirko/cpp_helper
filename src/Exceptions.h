#ifndef Exceptions_H
#define Exceptions_H

#include "CommonInclude.h"

#include <cstring>

namespace Exceptions
{

	class LeackExample
	{

		char* str;


	public:

		LeackExample( const char* data, size_t size ) throw( char* )
		{
			LOGOUT_FUNC
			str = new char[size];

			throw std::runtime_error( "" );

			strcpy( str, data );

			throw "exception in constructor";

		}
		virtual ~LeackExample() noexcept
		{
			LOGOUT_FUNC
			delete[] str;
		}


	};
	

	void example()
	{
		{
			try
			{
				char data[] = "Hello world";
				auto instance = new LeackExample( data, sizeof(data)/sizeof(char) );
			}
			catch ( const char* str )
			{
				std::cout << str << std::endl;
			}
			catch(...)
			{
				std::cout << "other exception" << std::endl;
			}
		}

	}

}


#endif