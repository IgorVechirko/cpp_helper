#ifndef Containers_H
#define Containers_H


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
#include <queue>>


namespace Containers
{
	void example()
	{
		std::array<int,4> intArray;

		std::vector<float> floatVector;

		std::deque<long> longDeque;

		std::list<char> charList;
		std::forward_list<unsigned> unsignedForwardList;

		std::set<std::string> stringSet;
		std::multiset<short> shortMultiset;
		
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

	}

}


#endif