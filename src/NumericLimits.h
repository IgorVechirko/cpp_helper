#ifndef NumericLimits_H
#define NumericLimits_H


#include "CommonInclude.h"


namespace NumericLimits
{

	void example()
	{
		std::cout << "int::max = " << std::numeric_limits<int>::max() << std::endl;
		std::cout << "int::min = " << std::numeric_limits<int>::min() << std::endl;
		std::cout << "int::epsilone = " << std::numeric_limits<int>::epsilon() << std::endl;
		std::cout << "int::has_infinity = " << std::numeric_limits<int>::has_infinity << std::endl;
		std::cout << "int::has_quiet_NaN = " << std::numeric_limits<int>::has_quiet_NaN << std::endl;

		std::cout << std::endl;

		std::cout << "float::max = " << std::numeric_limits<float>::max() << std::endl;
		std::cout << "float::min = " << std::numeric_limits<float>::min() << std::endl;
		std::cout << "float::epsilone = " << std::numeric_limits<float>::epsilon() << std::endl;
		std::cout << "float::has_infinity = " << std::numeric_limits<float>::has_infinity << std::endl;
		std::cout << "float::has_quiet_NaN = " << std::numeric_limits<float>::has_quiet_NaN << std::endl;
		std::cout << "float::quiet_NaN = " << std::numeric_limits<float>::quiet_NaN() << std::endl;

	}
}


#endif