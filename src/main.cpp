#include <iostream>

#include "FucnctionsAndMethodsPointers.h"
//#include "MemoryAllocations.h"//here override new/delete operators
#include "SmartPointers.h"
#include "Templates.h"
#include "Lambdas.h"
#include "DebugTools.h"
#include "ClassesAndStructures.h"
#include "VirtualAndOverrideKeyWords.h"
#include "FinalKeyWord.h"
#include "RTTIEmulation.h"
#include "RvalueLvalueSemantic.h"
#include "InlineFunctions.h"
#include "StaticLibUsing.h"
#include "DynamicLibUsing.h"
#include "ExplicitKeyWord.h"
#include "MutableKeyWord.h"
#include "ValotileRegisterKeyWords.h"
#include "ExternKeyWord.h"
#include "NumericLimits.h"
#include "MinMaxFuncs.h"
#include "Ratio.h"
#include "Chrono.h"
#include "Random.h"
#include "ParallelProgramming.h"
#include "Containers.h"
#include "Iterators.h"
#include "Algorithms.h"
#include "OperatorsOverrides.h"
#include "Attributes.h"
#include "Namespaces.h"
#include "Exceptions.h"
#include "FreeListAllocator.h"

int main()
{
	std::vector<int,FreeListAllocator> vector(1000);

	for( int i = 0; i < vector.size(); i++ )
		vector[i] = i;

	vector.erase( std::next( vector.begin(), 100 ) );


	std::cin.get();

	return 0;
}
