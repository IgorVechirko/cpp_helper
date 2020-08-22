#ifndef Ratio_H
#define Ratio_H

#include "CommonInclude.h"
#include <ratio>

namespace Ratio
{
	void example()
	{
		typedef std::ratio<1,1000000000> customNano;

		if ( std::ratio_equal< customNano, std::nano >() )
		{
			std::cout << "customNano equal to std::nano" << std::endl;
		}

		std::ratio<60,1> min;
		auto result = std::ratio_add<std::ratio<60,1>,std::ratio<120,1>>();
		std::cout << "result.num = " << result.num << std::endl;

	}

}

#endif