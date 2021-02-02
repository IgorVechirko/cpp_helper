#ifndef Iterators_H
#define Iterators_H


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


namespace Iterators
{
	void example()
	{
		std::array<int,4> intArray{ 4, 4, 4, 4 };

		std::vector<float> floatVector{ 1.0, 2.0f, 3.0f, 0.485f, 94.0, 0.343f };

		std::deque<long> longDeque;

		std::list<char> charList{ 33, 44, 66, 77, 62 };
		std::forward_list<unsigned> unsignedForwardList;

		std::set<std::string> stringSet;
		std::multiset<short> shortMultiset{ 73, 26, 47, 35 };
		
		std::map<int,std::string> intStringMap;
		std::multimap<std::string,int> stringIntMultimap;

		std::unordered_set<std::string> stringUnorderedSet;
		std::unordered_multiset<short> shortUnorderedMultiset;

		std::unordered_map<int,std::string> intStringUnorderedMap;
		std::unordered_multimap<std::string,int> stringIntUnorderedMultimap;

		//adaptors
		std::stack<double> doubleStack;
		std::queue<float> floatQueue;
		std::priority_queue<char> charPriorityQueue;


		std::copy( charList.begin(), charList.end(), std::back_inserter(floatVector) );
		std::copy( shortMultiset.begin(), shortMultiset.end(), std::inserter( floatVector, floatVector.begin() ) );
		
		auto advanceElemIt = floatVector.begin();
		auto advanceRElemIt = floatVector.rbegin();

		std::advance( advanceElemIt, 2 );
		std::advance( advanceElemIt, -2 );

		std::advance( advanceRElemIt, 2 );
		std::advance( advanceRElemIt, -2 );

		std::cout << "advanceElemIt = " << *advanceElemIt << std::endl;
		std::cout << "advanceRElemIt = " << *advanceRElemIt << std::endl; 

		std::cout << std::endl;


		auto nextPrevElemIt = std::next( floatVector.begin(), 4 );
		nextPrevElemIt = std::prev( nextPrevElemIt, 2 );

		auto nextPrevRElemIt = std::next( floatVector.rbegin(), 5 );
		nextPrevRElemIt = std::prev( nextPrevRElemIt, 1 );

		std::cout << "nextPrevElemIt = " << *nextPrevElemIt << std::endl;
		std::cout << "nextPrevRElemIt = " << *nextPrevRElemIt << std::endl;

		std::cout << std::endl;


		std::cout << "dist between advanceElemIt & nextPrevElemIt: " << std::distance( advanceElemIt, nextPrevElemIt ) << std::endl;
		std::cout << "dist between advanceRElemIt & nextPnextPrevRElemItrevElemIt: " << std::distance( advanceRElemIt, nextPrevRElemIt ) << std::endl;

		

	}

}


#endif