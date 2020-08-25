#ifndef ExternKeyWord_H
#define ExternKeyWord_H

#include "CommonInclude.h"


extern void useGlobalValueFunc1();
extern void useGlobalValueFunc2();
extern int globalValueForAllTranslationUnits;

namespace ExternKeyWord
{

	void example()
	{
		//globalValueForCurrenTranslationUnit++; //error
		std::cout << "globalValue start val -> " << globalValueForAllTranslationUnits << std::endl;
		useGlobalValueFunc1();
		useGlobalValueFunc2();
	}

}

#endif