#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#define LOGOUT_FUNC std::cout << __FUNCTION__ << std::endl;




namespace fucnctionsAndMethodsPointers
{
	struct returnType
	{
		int integer;
		char symb;
	};

	returnType function( int arg1, float arg2, const returnType& arg3 )
	{
		std::cout<< __FUNCTION__ << std::endl;

		return returnType();
	}

	class TestClass
	{
		public:	

			returnType method( long arg1, returnType* arg2 )
			{
				std::cout << __FUNCTION__ << std::endl;

				return returnType();
			}
	};


	void example()
	{
		returnType(*functionPtr)(int,float,const returnType&) = &function;
		functionPtr( 5, 0.2f, returnType() );

		TestClass instance;
		returnType(TestClass::*methodPtr)(long,returnType*) = &TestClass::method;
		returnType arg2;
		(instance.*methodPtr)( 5, &arg2 );
	}
};

namespace smartPointers
{
	class TestClass
	{
		public:
				
			TestClass()
			{
				LOGOUT_FUNC
			}
			
			virtual ~TestClass()
			{
				LOGOUT_FUNC
			}

	};

	void sharedPtrExample()
	{
		std::shared_ptr<TestClass> sparePtr;

		{
			auto sharedPtr = std::shared_ptr<TestClass>( new TestClass() );
			sparePtr = sharedPtr;
			std::cout << "finish local block" << std::endl;
		}

		std::cout << "finish " << __FUNCTION__ << " block" << std::endl;
	}

	void uniquePtrExample()
	{
		std::shared_ptr<TestClass> sparePtr;

		{
			auto uniquePtr = std::unique_ptr<TestClass>( new TestClass() );
			//sparePtr = uniquePtr; can'r create copy;
			std::cout << "finish local block" << std::endl;
		}
	}

	

	class SharedPtrCycleRelation
	{
		struct sGroup;
		struct sHuman
		{
			std::string name;
			std::vector<std::shared_ptr<sGroup>> groups;

			sHuman( const std::string& name )
			{
				this->name = name;
				LOGOUT_FUNC
			}
			~sHuman()
			{
				LOGOUT_FUNC
			}
		};

		struct sGroup
		{
			std::string name;
			std::vector<std::shared_ptr<sHuman>> humans;

			sGroup( const std::string& name )
			{
				this->name = name;
				LOGOUT_FUNC
			}
			~sGroup()
			{
				LOGOUT_FUNC
			}
		};

		std::vector<std::shared_ptr<sHuman>> humans;
		std::vector<std::shared_ptr<sGroup>> groups;

		public:

			SharedPtrCycleRelation()
			{
				LOGOUT_FUNC

				std::vector<std::string> persons = { "person1", "person2", "person3", "person4" };
				std::vector<std::string> casts = { "casta1", "casta2", "casta3", "casta4" };

				for( const auto& person : persons )
					humans.push_back( std::shared_ptr<sHuman>( new sHuman{ person } ) );

				for( const auto& casta : casts )
					groups.push_back( std::shared_ptr<sGroup>( new sGroup{ casta } ) );

				for( auto humanPtr : humans )
					humanPtr->groups = groups;

				for( auto groupPtr : groups )
					groupPtr->humans = humans;

			}
			virtual ~SharedPtrCycleRelation()
			{
				LOGOUT_FUNC
			}
	};

	class ResolveSharedPtrCycleRelationWithWeakPtr
	{
		struct sGroup;
		struct sHuman
		{
			std::string name;
			std::vector<std::weak_ptr<sGroup>> groups;

			sHuman( const std::string& name )
			{
				this->name = name;
				LOGOUT_FUNC
			}
			~sHuman()
			{
				LOGOUT_FUNC
			}
		};

		struct sGroup
		{
			std::string name;
			std::vector<std::weak_ptr<sHuman>> humans;

			sGroup( const std::string& name )
			{
				this->name = name;
				LOGOUT_FUNC
			}
			~sGroup()
			{
				LOGOUT_FUNC
			}
		};

		std::vector<std::shared_ptr<sHuman>> humans;
		std::vector<std::shared_ptr<sGroup>> groups;

		public:

			ResolveSharedPtrCycleRelationWithWeakPtr()
			{
				LOGOUT_FUNC

				std::vector<std::string> persons = { "person1", "person2", "person3", "person4" };
				std::vector<std::string> casts = { "casta1", "casta2", "casta3", "casta4" };

				for( const auto& person : persons )
					humans.push_back( std::shared_ptr<sHuman>( new sHuman{ person } ) );

				for( const auto& casta : casts )
					groups.push_back( std::shared_ptr<sGroup>( new sGroup{ casta } ) );

				for( const auto& humanPtr : humans )
				{
					for( const auto& groupPtr : groups )
					{
						humanPtr->groups.push_back( std::weak_ptr<sGroup>(groupPtr) );
					}
				}

				for( const auto& group : groups )
				{
					for( const auto& human : humans )
					{
						group->humans.push_back( std::weak_ptr<sHuman>( human ) );
					}
				}

			}
			virtual ~ResolveSharedPtrCycleRelationWithWeakPtr()
			{
				LOGOUT_FUNC
			}
	};


	void weakPtrExample()
	{
		{
			SharedPtrCycleRelation sharedPtrCycleRelation;
		}

		std::cout << std::endl << std::endl;

		{
			ResolveSharedPtrCycleRelationWithWeakPtr resolveSharedPtrCycleRelationWithWeakPtr;
		}
	}

};

namespace templates
{
	//template< typename TypesPackage >
	void tempalteFunctionWithTypesPackage()
	{
		std::cout << "last function" << std::endl;
	}

	template< typename T, typename... TypesPackage >
	void tempalteFunctionWithTypesPackage(const T& firstArg, const TypesPackage&... argsPackage )
	{
		std::cout << firstArg << std::endl;
		tempalteFunctionWithTypesPackage( argsPackage... );
	}

	void example()
	{
		tempalteFunctionWithTypesPackage( "sldkfj", 3, 6.598f, true );
	}
	

	//template alias
	template< typename T>
	class MyAllocator
	{
	};

	template<typename T>
	using MyVec = std::vector<T,MyAllocator<T>>;

};

namespace lambdas
{
	void example()
	{
		std::string capturedVal = "captured val";
		std::string otherVal = "other val";

		auto lambdaWithCapturedByValue = [=,&capturedVal](){
			LOGOUT_FUNC
			std::cout << "capturedVal = " << capturedVal << std::endl;
			std::cout << "other val = " << otherVal << std::endl;
		};

		auto lambdaWithCapturedByRef = [&,capturedVal](){
			LOGOUT_FUNC
			std::cout << "capturedVal = " << capturedVal << std::endl;
			std::cout << "other val = " << otherVal << std::endl;
		};

		capturedVal = "new captured val";
		otherVal = "new other val";

		lambdaWithCapturedByValue();
		lambdaWithCapturedByRef();

		auto lambdaWithArgsAndReturnType = []( auto argToReturn ) -> auto { return argToReturn; };
		std::cout << lambdaWithArgsAndReturnType( "lambdaWithArgsAndReturnType" ) << std::endl;
	}
};

namespace debugTools
{
	void example()
	{
		float arr[10000];

		srand(time(nullptr));

		for( int indx = 0; indx < 10000; indx++ )
		{
			float logoutValueIfMoreThen0_95 = (float)rand() / (float)RAND_MAX;
			arr[indx] = logoutValueIfMoreThen0_95;
		}

		LOGOUT_FUNC
	}
};

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

namespace VirtualAndOverride
{

	class BaseClass
	{
		public:
		
			void noVirualMethod()
			{
				std::cout << "BaseClass::noVirualMethod" << std::endl;
			}
			
			virtual void virtualMethod1()
			{
				std::cout << "BaseClass::virtualMethod1" << std::endl;
			}
		
			virtual void virtualMethod2()
			{
				std::cout << "BaseClass::virtualMethod2" << std::endl;
			}
	};

	class FirstChild : public BaseClass
	{
		public:
		
			void noVirualMethod()
			{
				std::cout << "FirstChild::noVirualMethod" << std::endl;
			}
		
			void virtualMethod1()
			{
				std::cout << "FirstChild::virtualMethod1" << std::endl;
			}
		
			void virtualMethod2() override
			{
				std::cout << "FirstChild::virtualMethod2" << std::endl;
			}
	};

	class SecondChild : public FirstChild
	{
		public:
		
			void noVirualMethod()
			{
				std::cout << "SecondChild::noVirualMethod" << std::endl;
			}
		
			void virtualMethod1()
			{
				std::cout << "SecondChild::virtualMethod1" << std::endl;
			}
		
			virtual void virtualMethod2() override
			{
				std::cout << "SecondChild::virtualMethod2" << std::endl;
			}
	};

	

	void example()
	{
		FirstChild* instance = new SecondChild();
		
		instance->noVirualMethod();
		instance->virtualMethod1();
		instance->virtualMethod2();
		instance->BaseClass::virtualMethod2();
		
		
		
		delete instance;
	}
}

namespace FinalKeyWord
{
	
	class BaseClass
	{
		public:
		
			virtual void virtuaMethod()
			{
				LOGOUT_FUNC
			}
		
	};

	class FistChildClass : public BaseClass
	{
		public:
		
			virtual void virtuaMethod() final // final can be hint for compiler for optimize
			{
				LOGOUT_FUNC
			}
	};

	class SecondChildClass final : public FistChildClass
	{
		/*virtual void virtuaMethod() final //not available
		{
			LOGOUT_FUNC
		}*/
	};

	class thirdChildClass //: public SecondChildClass// not available
	{
		
	};


	void example()
	{
		BaseClass* instance = new SecondChildClass();
		
		instance->virtuaMethod();
		
		delete instance;
		
	};

}


int main()
{
	FinalKeyWord::example();

	std::cin.get();

	return 0;
}
