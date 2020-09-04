#ifndef ExplicitKeyWord_H
#define ExplicitKeyWord_H

#include "CommonInclude.h"
#include <string>

namespace ExplicitKeyWord
{
	class TestClass
	{
		std::string _name;
		int _integer{0};

	public:

		TestClass()
		{
		}

		TestClass(const std::string& name )
			: _name( name )
		{
			LOGOUT_FUNC
		}

		TestClass( int integer )
			: _integer( integer )
		{
			LOGOUT_FUNC
		}

		explicit TestClass( const std::string& name, int integer )
			: _name( name )
			, _integer( integer )
		{
			LOGOUT_FUNC
		}

		operator int()
		{
			return _integer;
		}

		explicit operator std::string()
		{
			return _name;
		}
	};

	void example()
	{
		TestClass a = std::string( "Instance1" );
		TestClass b = 2;
		//TestClass c = { "Instance3", 3 }; implicit conversation disabled
		TestClass c = TestClass( "Instance3", 3 );

		std::cout << std::endl;

		int instance3Integer = c;
		std::cout << "instance3Integer = " << c << std::endl << std::endl;

		//std::string instance3Name = c; implicit conversation disabled
		std::string instance3Name = (std::string)c;
		std::cout << "instance3Name = " << instance3Name << std::endl;
	}
}

#endif