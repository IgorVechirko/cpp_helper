#include "ClassesAndStructures.h"

std::string ClassesAndStructures::BaseClass::_staticMember = "THIS IS STATIC MEMBER";

namespace ClassesAndStructures
{
	//BaseStruct
	void BaseStruct::structVirtualMethod()
	{
		std::cout << "structVirtualMethod member = " << baseStructMember << std::endl;
	}


	//ChildStruct
	void ChildStruct::structVirtualMethod()
	{
		std::cout << "structVirtualMethod member = " << childStructMember << std::endl;
	}
	
	//BaseClass
	BaseClass::BaseClass()
	{
		std::cout << "_staticMember = " << _staticMember << std::endl;
	}

	void BaseClass::classVirtualMethod()
	{
		std::cout << "classVirtualMethod member = " << baseClassMember << std::endl;
	}

	//ChildClass
	void ChildClass::classVirtualMethod()
	{
		std::cout << "classVirtualMethod member = " << childClassMember << std::endl;
	}

	//TestStruct
	void TestStruct::classVirtualMethod()
	{
		std::cout << "classVirtualMethod member = " << baseStructMember << std::endl;
		std::cout << "classVirtualMethod member = " << BaseStruct::baseStructMember << std::endl;
	}
		
	//ChildeClass1
	ChildeClass1::ChildeClass1()
	{
	}

	ChildeClass1::~ChildeClass1()
	{
	};

	//ChildeClass2
	ChildeClass2::ChildeClass2()
	{
	}

	ChildeClass2::~ChildeClass2()
	{
	};


	//MultipleInheritanceClass
	MultipleInheritanceClass::MultipleInheritanceClass()
	{
		LOGOUT_FUNC
	}
	MultipleInheritanceClass::~MultipleInheritanceClass()
	{
		LOGOUT_FUNC
	}


	//ConstructionFirstBaseClass
	ConstructionFirstBaseClass::ConstructionFirstBaseClass()
	{
		LOGOUT_FUNC
	}
	ConstructionFirstBaseClass::~ConstructionFirstBaseClass()
	{
		LOGOUT_FUNC
	}

	//ConstructionSecondBaseClass
	ConstructionSecondBaseClass::ConstructionSecondBaseClass()
	{
		LOGOUT_FUNC
	}
	ConstructionSecondBaseClass::~ConstructionSecondBaseClass()
	{
		LOGOUT_FUNC
	}


	//ConstructionMember1
	ConstructionMember1::ConstructionMember1()
	{
		LOGOUT_FUNC
	}
	ConstructionMember1::~ConstructionMember1()
	{
		LOGOUT_FUNC
	}


	//ConstructionMember2
	ConstructionMember2::ConstructionMember2()
	{
		LOGOUT_FUNC
	}
	ConstructionMember2::~ConstructionMember2()
	{
		LOGOUT_FUNC
	}


	//ConstructClass
	ConstructClass::ConstructClass()
		: ConstructionSecondBaseClass()
		, ConstructionFirstBaseClass()
		, member2()
		, member1()
	{
		LOGOUT_FUNC
	}
	ConstructClass::~ConstructClass()
	{
		LOGOUT_FUNC
	}



	void example()
	{
		LOGOUT_FUNC
		{
			TestClass testClassInstance;
		
			//std::cout << testClassInstance.baseStructMember << std::endl;// no access
			//std::cout << testClassInstance.baseClassMember << std::endl;// no access
			//std::cout << testClassInstance.childStructMember << std::endl;// no access
			std::cout << "has access to " << testClassInstance.childClassMember << std::endl;
			//testClassInstance.structVirtualMethod(); / no access
			testClassInstance.classVirtualMethod();
		
			TestStruct testStructInstance;
			std::cout << "has access to " << testStructInstance.baseStructMember << std::endl;
			//std::cout << testStructInstance.baseClassMember << std::endl;// no access
			std::cout << "has access to " << testStructInstance.childStructMember << std::endl;
			std::cout << "has access to " << testStructInstance.childClassMember << std::endl;
			testStructInstance.structVirtualMethod();
			testStructInstance.classVirtualMethod();
		}

		std::cout << std::endl;

		{
			MultipleInheritanceClass instance;
			instance.classVirtualMethod();//multiple inheritance solved throw using virtual inheritance

		}

		std::cout << std::endl;

		{
			ConstructClass instance;
		}
	

	}
}