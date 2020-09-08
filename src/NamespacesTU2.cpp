#include "Namespaces.h"

namespace
{
	void trnaslationUnitStaticFunc()
	{
		std::cout << "Translation unit 2" << std::endl;
	}
}

void translationUnit2::printBehavior()
{
	trnaslationUnitStaticFunc();
}