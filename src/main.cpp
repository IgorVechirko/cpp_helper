#include <iostream>


//stl
#include "Algorithms.h"
#include "Iterators.h"
#include "Containers.h"

#include "Attributes.h"
#include "ClassesAndStructures.h"
#include "FinalKeyWord.h"
#include "FucnctionsAndMethodsPointers.h"
#include "InlineFunctions.h"
#include "Lambdas.h"
#include "RvalueLvalueSemantic.h"
#include "SmartPointers.h"
#include "Templates.h"
#include "VirtualAndOverrideKeyWords.h"
#include "ExplicitKeyWord.h"
#include "MutableKeyWord.h"
#include "ValotileRegisterKeyWords.h"
#include "ParallelProgramming.h"
#include "NumericLimits.h"
#include "MinMaxFuncs.h"
#include "Chrono.h"
#include "Exceptions.h"
#include "OperatorsOverrides.h"
#include "Namespaces.h"
#include "DebugTools.h"
#include "ExternKeyWord.h"
#include "Random.h"
#include "MemoryOrder.h"

#include "StaticLibUsing.h"

#include "DynamicStaticPlugInLibUsing.h"
#include "DynamicDynamicPlugInLibUsing.h"

#include "TCPServerSocket.h"
#include "TCPClientSocket.h"

#include "ParallelQueue.h"
#include "ParallelLookupTable.h"

//not finished
//#include "MemoryAllocations.h"
//#include "RTTIEmulation.h"


static ParallelLookupTable<int,std::string> table;

template<typename T, typename Y>
static void increaseTable(ParallelLookupTable<T, Y>* table)
{
	std::default_random_engine dre;
	std::uniform_int_distribution<T> di{1,200};
	auto key = di(dre);

	table->addOrUpdate(key, std::string("String_") + std::to_string(key));
}

template<typename T, typename Y>
static void readTable(ParallelLookupTable<T, Y>* table)
{
	std::default_random_engine dre;
	std::uniform_int_distribution<T> di{1,200};
	auto key = di(dre);

	const auto& value = table->getValue(key, "");

	if(value != "")
	{
		std::cout << value << std::endl;
	}
	else
	{
		std::cout << "No value for key " << key << std::endl;
	}
}


int main()
{
	std::array<std::shared_ptr<std::thread>, 5> inserters;
	for(auto& thread : inserters)
	{
		thread = std::make_shared<std::thread>(increaseTable<int32_t,std::string>, &table);
	}

	std::array<std::shared_ptr<std::thread>, 5> readers;
	for(auto& thread : readers)
	{
		thread = std::make_shared<std::thread>(readTable<int32_t,std::string>, &table);
	}

	for(auto& thread : inserters)
	{
		thread->join();
	}

	for(auto& thread : readers)
	{
		thread->join();
	}
	
	const auto& map = table.getMap();

	return 0;
}
