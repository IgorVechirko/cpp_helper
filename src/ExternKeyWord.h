#ifndef ExternKeyWord_H
#define ExternKeyWord_H

#include "CommonInclude.h"


extern void useGlobalValueFunc1();
extern void useGlobalValueFunc2();
extern int globalValue;

namespace ExternKeyWord
{

	void example()
	{
		std::cout << "globalValue start val -> " << globalValue << std::endl;
		useGlobalValueFunc1();
		useGlobalValueFunc2();
	}

}

#endif