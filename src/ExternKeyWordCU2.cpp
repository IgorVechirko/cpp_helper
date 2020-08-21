#include <iostream>

extern int globalValue;

void useGlobalValueFunc2()
{
	globalValue++;
	std::cout << __FUNCTION__ << " globalValue = " << globalValue << std::endl;
}