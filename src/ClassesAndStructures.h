#ifndef ClassesAndStructures_H
#define ClassesAndStructures_H

#include "CommonInclude.h"

namespace ClassesAndStructures
{

	struct BaseStruct
	{
		std::string baseStructMember = "baseStructMember";
		
		virtual void structVirtualMethod()
		{
			std::cout << "structVirtualMethod member = " << baseStructMember << std::endl;
		}
	};

	struct ChildStruct : BaseStruct // same as public
	{
		std::string childStructMember = "childStructMember";
		
		void structVirtualMethod() override
		{
			std::cout << "structVirtualMethod member = " << childStructMember << std::endl;
		}
	};
	
	class BaseClass
	{
		public:
		
			std::string baseClassMember = "baseClassMember";
		
			virtual void classVirtualMethod()
			{
				std::cout << "classVirtualMethod member = " << baseClassMember << std::endl;
			}
	};

	class ChildClass : BaseClass // same as private
	{
		public:
			
			std::string childClassMember = "childClassMember";
		
			void classVirtualMethod() override
			{
				std::cout << "classVirtualMethod member = " << childClassMember << std::endl;
			}
	};

	class TestClass : ChildStruct // same as private
					, public ChildClass
	{
		
	};

	struct TestStruct : ChildStruct
					  , ChildClass
	{
		std::string baseStructMember = "testStructMember";
		
		void classVirtualMethod() override
		{
			std::cout << "classVirtualMethod member = " << baseStructMember << std::endl;
			std::cout << "classVirtualMethod member = " << BaseStruct::baseStructMember << std::endl;
		}
		
	};


	void example()
	{
		LOGOUT_FUNC
		
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
}

#endif