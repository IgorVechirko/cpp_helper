#include <iostream>

extern int globalValueForAllTranslationUnits;

static int globalValueForCurrenTranslationUnit = 1;

void useGlobalValueFunc2()
{
	globalValueForAllTranslationUnits++;
	std::cout << __FUNCTION__ << " globalValueForAllTranslationUnits = " << globalValueForAllTranslationUnits << std::endl;
	std::cout << __FUNCTION__ << " globalValueForCurrenTranslationUnit = " << globalValueForCurrenTranslationUnit << std::endl;

}