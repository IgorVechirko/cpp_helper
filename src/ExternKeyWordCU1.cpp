#include <iostream>

int globalValueForAllTranslationUnits = 1;

void useGlobalValueFunc1()
{
	globalValueForAllTranslationUnits++;
	std::cout << __FUNCTION__ << " globalValueForAllTranslationUnits = " << globalValueForAllTranslationUnits << std::endl;
}