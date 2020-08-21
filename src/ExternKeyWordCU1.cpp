#include <iostream>

int globalValue = 1;

void useGlobalValueFunc1()
{
	globalValue++;
	std::cout << __FUNCTION__ << " globalValue = " << globalValue << std::endl;
}