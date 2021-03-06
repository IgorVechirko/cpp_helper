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

#include "StaticLibUsing.h"

#include "DynamicStaticPlugInLibUsing.h"
#include "DynamicDynamicPlugInLibUsing.h"

#include "TCPServerSocket.h"
#include "TCPClientSocket.h"

//not finished
//#include "MemoryAllocations.h"
//#include "RTTIEmulation.h"


int main()
{
	auto clientRoutine = [](){
		Sleep(100);
		TCPClientSocket::example();
	};

	std::thread clientThread( clientRoutine );
	clientThread.detach();

	TCPServerSocket::example();

	std::cin.get();

	return 0;
}
