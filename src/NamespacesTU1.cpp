#include "Namespaces.h"


namespace TestNamespace
{
	void nestedFunc()
	{
		LOGOUT_FUNC
	}

	void otherNestedFunc()
	{
		LOGOUT_FUNC
	}

	inline namespace NestedNamespace1
	{
		void doubleNestedFunc()
		{
			LOGOUT_FUNC
		}

		inline namespace NestedNamespace2
		{
			void thirdNestedFunc()
			{
				LOGOUT_FUNC
			}
		}
	}

}


void Namespaces::example()
{
	using TestNamespace::otherNestedFunc;
	namespace namespaceAlias = TestNamespace::NestedNamespace1::NestedNamespace2;
	
	TestNamespace::nestedFunc();
	otherNestedFunc();
	TestNamespace::doubleNestedFunc();
	TestNamespace::thirdNestedFunc();
	namespaceAlias::thirdNestedFunc();

	translationUnit1::printBehavior();
	translationUnit2::printBehavior();
}













namespace
{
	void trnaslationUnitStaticFunc()
	{
		std::cout << "Translation unit 1" << std::endl;
	}
}

void translationUnit1::printBehavior()
{
	trnaslationUnitStaticFunc();
}