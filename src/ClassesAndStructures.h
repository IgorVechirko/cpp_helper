#ifndef ClassesAndStructures_H
#define ClassesAndStructures_H

#include "CommonInclude.h"
#include <string>

namespace ClassesAndStructures
{

	struct BaseStruct
	{
		std::string baseStructMember = "baseStructMember";
		
		virtual void structVirtualMethod();
	};

	struct ChildStruct : BaseStruct // same as public
	{
		std::string childStructMember = "childStructMember";
		
		void structVirtualMethod() override;
	};
	
	class BaseClass
	{
		static std::string _staticMember;//static member declaration. Static member must be defined out of class scope

		public:
		
			std::string baseClassMember = "baseClassMember";
		
			BaseClass();

			virtual void classVirtualMethod();
	};


	class ChildClass : BaseClass // same as private
	{
		public:
			
			std::string childClassMember = "childClassMember";
		
			void classVirtualMethod() override;
	};

	class TestClass : ChildStruct // same as private
					, public ChildClass
	{
		
	};

	struct TestStruct : ChildStruct
					  , ChildClass
	{
		std::string baseStructMember = "testStructMember";
		
		void classVirtualMethod() override;
		
	};

	class ChildeClass1 : virtual public BaseClass
	{
	public:

		ChildeClass1();

		virtual ~ChildeClass1();
	};

	class ChildeClass2 : virtual public BaseClass
	{
	public:

		ChildeClass2();

		virtual ~ChildeClass2();
	};

	class MultipleInheritanceClass : public ChildeClass1 , public ChildeClass2
	{
	public:

		MultipleInheritanceClass();

		virtual ~MultipleInheritanceClass();

	};


	class ConstructionFirstBaseClass
	{
	public:

		ConstructionFirstBaseClass();

		virtual ~ConstructionFirstBaseClass();
	};

	class ConstructionSecondBaseClass
	{

	public:

		ConstructionSecondBaseClass();

		virtual ~ConstructionSecondBaseClass();

	};

	class ConstructionMember1
	{

	public:

		ConstructionMember1();

		virtual ~ConstructionMember1();

	};

	class ConstructionMember2
	{

	public:

		ConstructionMember2();

		virtual ~ConstructionMember2();
	};

	class ConstructClass 
		: public ConstructionFirstBaseClass
		, public ConstructionSecondBaseClass
	{

		ConstructionMember1 member1;
		ConstructionMember2 member2;

		
	public:

		ConstructClass();

		virtual ~ConstructClass();
	};


	void example();

}

#endif