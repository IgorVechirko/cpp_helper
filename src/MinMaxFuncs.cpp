#include "MinMaxFuncs.h"

#include "CommonInclude.h"
#include <algorithm>

namespace MinMaxFuncs
{
	void example()
	{
		auto reversComparator = [](auto a, auto b ) -> bool { return b < a; };

		std::cout << "min from 4 & 5 = " << std::min( 4, 5 ) << std::endl;
		std::cout << "revers min from 4 & 5 = " << std::min( 4, 5, reversComparator ) << std::endl;
		std::cout << "min from 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 = " << std::min( { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f } ) << std::endl;
		std::cout << "revers min from 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 = " << std::min( { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f }, reversComparator ) << std::endl;

		std::cout << std::endl;

		std::cout << "max from 4 & 5 = " << std::max( 4, 5 ) << std::endl;
		std::cout << "revers max from 4 & 5 = " << std::max( 4, 5, reversComparator ) << std::endl;
		std::cout << "max from 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 = " << std::max( { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f } ) << std::endl;
		std::cout << "revers max from 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 = " << std::max( { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f }, reversComparator ) << std::endl;

		std::cout << std::endl;

		{
			auto resultPair = std::minmax( 5, 4 );
			std::cout << "minmax from 5 & 4 = " << resultPair.first << " " << resultPair.second << std::endl;
		}

		{
			auto resultPair = std::minmax( 5, 4, reversComparator );
			std::cout << "revers minmax from 5 & 4 = " << resultPair.first << " " << resultPair.second << std::endl;
		}

		{
			auto resultPair = std::minmax( { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f } );
			std::cout << "minmax from 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 = " << resultPair.first << " " << resultPair.second << std::endl;
		}

		{
			auto resultPair = std::minmax( { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f }, reversComparator );
			std::cout << "revers minmax from 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 = " << resultPair.first << " " << resultPair.second << std::endl;
		}
	}

}