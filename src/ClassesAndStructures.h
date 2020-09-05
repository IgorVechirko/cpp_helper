#ifndef ClassesAndStructures_H
#define ClassesAndStructures_H

#include "CommonInclude.h"
#include <string>

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
		static std::string _staticMember;//static member declaration. Static member must be defined out of class scope

		public:
		
			std::string baseClassMember = "baseClassMember";
		
			BaseClass()
			{
				std::cout << "_staticMember = " << _staticMember << std::endl;
			}

			virtual void classVirtualMethod()
			{
				std::cout << "classVirtualMethod member = " << baseClassMember << std::endl;
			}
	};

	std::string BaseClass::_staticMember = "THIS IS STATIC MEMBER";


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

	class ChildeClass1 : virtual public BaseClass
	{
	public:

		ChildeClass1()
		{
		}

		virtual ~ChildeClass1()
		{
		};
	};

	class ChildeClass2 : virtual public BaseClass
	{
	public:

		ChildeClass2()
		{
		}

		virtual ~ChildeClass2()
		{
		};
	};

	class MultipleInheritanceClass : public ChildeClass1 , public ChildeClass2
	{
	public:

		MultipleInheritanceClass()
		{
			LOGOUT_FUNC
		}
		virtual ~MultipleInheritanceClass()
		{
			LOGOUT_FUNC
		}

	};


	class ConstructionFirstBaseClass
	{
	public:

		ConstructionFirstBaseClass()
		{
			LOGOUT_FUNC
		}
		virtual ~ConstructionFirstBaseClass()
		{
			LOGOUT_FUNC
		}
	};

	class ConstructionSecondBaseClass
	{

	public:

		ConstructionSecondBaseClass()
		{
			LOGOUT_FUNC
		}
		virtual ~ConstructionSecondBaseClass()
		{
			LOGOUT_FUNC
		}

	};

	class ConstructionMember1
	{

	public:

		ConstructionMember1()
		{
			LOGOUT_FUNC
		}
		virtual ~ConstructionMember1()
		{
			LOGOUT_FUNC
		}
	};

	class ConstructionMember2
	{

	public:

		ConstructionMember2()
		{
			LOGOUT_FUNC
		}
		virtual ~ConstructionMember2()
		{
			LOGOUT_FUNC
		}
	};

	class ConstructClass 
		: public ConstructionFirstBaseClass
		, public ConstructionSecondBaseClass
	{

		ConstructionMember1 member1;
		ConstructionMember2 member2;

		
	public:

		ConstructClass()
			: ConstructionSecondBaseClass()
			, ConstructionFirstBaseClass()
			, member2()
			, member1()
		{
			LOGOUT_FUNC
		}
		virtual ~ConstructClass()
		{
			LOGOUT_FUNC
		}
	};



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

#endif