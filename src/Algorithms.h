#ifndef Algorithms_H
#define Algorithms_H


#include "CommonInclude.h"
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>


namespace Algorithms
{
	void example()
	{
		// see https://en.cppreference.com/w/cpp/algorithm

		{
			std::vector<int> coll(10);
			for( int i = 0; i < coll.size(); i++ )
				coll[i] = i;

			std::remove_if( coll.begin(), coll.end(), [](int elem) {
				return elem == 5;
			});

			std::cout << "without removing remaining elems" << std::endl;
			for( auto elem : coll )
				std::cout << elem << " ";
			std::cout << std::endl;

			coll.resize( coll.size() - 1 );

			std::cout << "with removing remaining elems" << std::endl;
			for( auto elem : coll )
				std::cout << elem << " ";
			std::cout << std::endl;

		}

	}

}


#endif