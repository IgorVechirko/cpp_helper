#ifndef InlineFunctions_H
#define InlineFunctions_H

#include "CommonInclude.h"


namespace InlineFunctions
{
	/* inline it's hint for compiler, it's isn't necessary that in finish code function will be inline.
	For compilers exist options for setup depth for recursive inline funcions nesting*/
	inline unsigned factorial( int a )
	{
		std::cout << __LINE__ << std::endl;

		if ( a == 1 )
			return 1;
		else
			return a * factorial( a-1 );
	}

	void example()
	{
		std::cout << "Factorial 10 = " << factorial(10) << std::endl;
	}
};


#endif