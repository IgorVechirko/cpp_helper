#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iterator>

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

/*void* operator new ( std::size_t count )
{
	std::cout << "operator new" << std::endl;
	return malloc(count);
}
void* operator new ( std::size_t count, const std::nothrow_t& tag )
{
	std::cout << "operator new ( nothrow )" << std::endl;
	return malloc(count);
}

void* operator new[] ( std::size_t count )
{
	std::cout << "operator new[]" << std::endl;
	return malloc(count);
}
void* operator new[] ( std::size_t count, const std::nothrow_t& tag )
{
	std::cout << "operator new[] ( nothrow )" << std::endl;
	return malloc(count);
}

void* operator new ( std::size_t count, int num )
{
	std::cout << "placement operator new num = " << num << std::endl;

	return new char[count];
}*/


namespace memoryAllocations
{
	class TestAllocation
	{
		int _member;

		public:

			TestAllocation()
				: _member( 0 )
			{LOGOUT_FUNC};
			TestAllocation( int member )
				: _member( member )
			{};
			virtual ~TestAllocation(){LOGOUT_FUNC};
	};

	class OverrideOperatorNewAllocation
	{
		public:

			OverrideOperatorNewAllocation(){LOGOUT_FUNC};
			virtual ~OverrideOperatorNewAllocation(){LOGOUT_FUNC};

			
			void* operator new( size_t size )
			{
				LOGOUT_FUNC
				void* result = new char[sizeof(OverrideOperatorNewAllocation)];

				return result;
			}
	};

	void exampleNewExpression()
	{
		LOGOUT_FUNC

		auto intsArray = new( int[10] );
		auto intsArray2 = new int[10];
		auto funcPointersArray = new ( int(*[10])(int, float) );
		//auto funcPintersArray = new int(*[10])(int, float); error (new int) (*[10]())

		delete[] intsArray;
		delete[] intsArray2;
		delete[] funcPointersArray;

		auto allocateWithInitializer = new TestAllocation();
		auto allocateWithoutInitializer = new TestAllocation;
		auto allocateWithAutoType = new auto( *allocateWithoutInitializer );

		delete allocateWithInitializer;
		delete allocateWithoutInitializer;
		delete allocateWithAutoType;
	}

	void examplePlacementNew()
	{
		LOGOUT_FUNC

		auto memoryForObject = new char[sizeof(TestAllocation)];
		auto createByPlacementNew = new (memoryForObject)(TestAllocation);

		std::cout << "memoryForObject address = " << (void*)memoryForObject << " createByPlacementNew obj address = " << createByPlacementNew << std::endl; 

		createByPlacementNew->~TestAllocation();
		delete [] memoryForObject;
	}

	void exampleNewOperatorOverrides()
	{
		auto newExpressionOverride = new TestAllocation();
		auto newNothrowExpressionOverride = new(std::nothrow) TestAllocation();
		auto newArrayExpressionOverride = new TestAllocation[2];
		auto newNothrowArrayExpressionOverride = new(std::nothrow) TestAllocation[2];

		delete newExpressionOverride;
		delete newNothrowExpressionOverride;
		delete[] newArrayExpressionOverride;
		delete[] newNothrowArrayExpressionOverride;

		auto memoryForObject = new char[sizeof(TestAllocation)];
		auto placementCreatedObj = new ( memoryForObject ) (TestAllocation);

		placementCreatedObj->~TestAllocation();
		delete[] memoryForObject;
	}

}

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
		std::cout << "args count = " << sizeof...(TypesPackage) << std::endl;

		std::cout << firstArg << std::endl;
		tempalteFunctionWithTypesPackage( argsPackage... );
	}

	void example()
	{
		tempalteFunctionWithTypesPackage( "", 5, 0.054f, true );
		tempalteFunctionWithTypesPackage( 5, 0.054, true );
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




namespace RTTIEmulation
{
	/*void collectTypes( std::vector<int>& collection )
	{
		LOGOUT_FUNC
	}

	template< typename First >
	void collectTypes( std::vector<int>& collection )
	{
		auto resultTypes = First::getTypesList();
		if ( resultTypes )
		{
			std::copy( resultTypes->begin(), resultTypes->end(), std::inserter( collection, collection.end() ) );
		}
	}

	template< typename First, typename... Others >
	void collectTypes( std::vector<int>& collection, First* firstArg )
	{
		auto resultTypes = First::getTypesList();
		if ( resultTypes )
		{
			std::copy( resultTypes->begin(), resultTypes->end(), std::inserter( collection, collection.end() ) );
		}
		openTypesPack<Others...>(collection);
	}

	template< typename First, typename... Others >
	void openTypesPack( std::vector<int>& collection )
	{
		collectTypes( collection, (First*)nullptr );
	}

	#define GET_TYPES_LIST_FUNC_1(__TYPE_ID__)\
	static const std::vector<int>* getTypesList()\
	{\
		static std::vector<int> typesList;\
		if( typesList.empty() )\
		{\
			typesList.push_back( __TYPE_ID__ );\
		}\
		return &typesList;\
	}\

	#define GET_TYPES_LIST_FUNC_2(__TYPE_ID__, ...)\
	static const std::vector<int>* getTypesList()\
	{\
		static std::vector<int> typesList;\
		if( typesList.empty() )\
		{\
			openTypesPack<__VA_ARGS__>(typesList);\
			typesList.push_back( __TYPE_ID__ );\
		}\
		return &typesList;\
	}\*/
	
	void copyVecs( std::vector<int>& output, const std::vector<int>& input )
	{
		std::copy( input.rbegin(), input.rend(), std::inserter( output, output.end() ) );
	}
	

	class FirstTreeBase
	{

		public:

			static int getTypeID(){return 0;};
			static const std::vector<int>& getTypesList()
			{
				static std::vector<int> typesList;
				if( typesList.empty() )
				{
					typesList.push_back( getTypeID() );
				}

				return typesList;
			}

			FirstTreeBase(){};
			virtual ~FirstTreeBase(){};
	};

	class FirstTreeChild : public FirstTreeBase
	{
		public:

			static int getTypeID(){return 1;};
			static const std::vector<int>& getTypesList()
			{
				static std::vector<int> typesList;
				if( typesList.empty() )
				{
					typesList.push_back( getTypeID() );
					copyVecs( typesList, FirstTreeBase::getTypesList() );
				}

				return typesList;
			}

			FirstTreeChild(){};
			virtual ~FirstTreeChild(){};
	};

	class FirstTreeSecondaryChild : public FirstTreeChild
	{
		public:

				static int getTypeID(){return 2;};
				static const std::vector<int>& getTypesList()
				{
					static std::vector<int> typesList;
					if( typesList.empty() )
					{
						typesList.push_back( getTypeID() );
						copyVecs( typesList, FirstTreeChild::getTypesList() );
					}

					return typesList;
				}

				FirstTreeSecondaryChild(){};
				virtual ~FirstTreeSecondaryChild(){};
	};



	class SecondTreeBase
	{
		public:

			static int getTypeID(){return 3;};
			static const std::vector<int>& getTypesList()
				{
					static std::vector<int> typesList;
					if( typesList.empty() )
					{
						typesList.push_back( getTypeID() );
					}

					return typesList;
				}

			SecondTreeBase(){};
			virtual ~SecondTreeBase(){};
	};

	class SecondTreeChild : public SecondTreeBase
	{
		public:

			static int getTypeID(){return 4;};
			static const std::vector<int>& getTypesList()
			{
				static std::vector<int> typesList;
				if( typesList.empty() )
				{
					typesList.push_back( getTypeID() );
					copyVecs( typesList, SecondTreeBase::getTypesList() );
				}

				return typesList;
			}

			SecondTreeChild(){};
			virtual ~SecondTreeChild(){};
	};

	class SecondTreeSecondaryChild : public SecondTreeChild
	{
		public:

				static int getTypeID(){return 5;};
				static const std::vector<int>& getTypesList()
				{
					static std::vector<int> typesList;
					if( typesList.empty() )
					{
						typesList.push_back( getTypeID() );
						copyVecs( typesList, SecondTreeChild::getTypesList() );
					}

					return typesList;
				}

				SecondTreeSecondaryChild(){};
				virtual ~SecondTreeSecondaryChild(){};
	};


	class TreesCombine 
		: public SecondTreeSecondaryChild
		, public FirstTreeSecondaryChild
	{
		public:
			
			static int getTypeID(){return 6;};
			static const std::vector<int>& getTypesList()
			{
				static std::vector<int> typesList;
				if( typesList.empty() )
				{
					typesList.push_back( getTypeID() );
					copyVecs( typesList, SecondTreeSecondaryChild::getTypesList() );
					copyVecs( typesList, FirstTreeSecondaryChild::getTypesList() );
				}

				return typesList;
			}

			TreesCombine(  ){};
			virtual ~TreesCombine(){};
	};

	template<typename T, typename... Types>
	T* createCastedObj( const Types&... args )
	{
		auto headerSize = sizeof(uintptr_t);
		auto objSize = sizeof(T);
		
		void* headerPtr = new uint8_t[objSize+headerSize];
		void* objPtr = (char*)headerPtr + headerSize;
		
		T* result = new(objPtr) T(args...);
		
		std::cout << "createCastedObj headerPtr = " << headerPtr << ", objPtr = " << objPtr << ", result = " << result << std::endl;
		
		return result;
	}

	template< typename T, typename Y>
	T* my_dynamic_cast(Y* convertPtr )
	{
		if ( !convertPtr )
			return nullptr;
		
		auto headerPtr = reinterpret_cast<const std::vector<int>**>( (uintptr_t)convertPtr - 8 );
		
		std::cout << " convertPtr = " << convertPtr << ", headerPtr = " << headerPtr << std::endl;
		
		//auto vec = (*(*headerPtr));
		
		bool stop = true;

		return nullptr;
	};

	void example()
	{
		LOGOUT_FUNC

		auto firstTreeChildInstance = new TreesCombine(); //createCastedObj<TreesCombine>();
		auto castedPtr = static_cast<FirstTreeSecondaryChild*>(firstTreeChildInstance);
		std::cout << "firstTreeChildInstance = " << (void*)firstTreeChildInstance << ", castedPtr = " << (void*)castedPtr << std::endl;
		auto secondTreeChildInstance = my_dynamic_cast<SecondTreeChild>(firstTreeChildInstance);

		if ( secondTreeChildInstance )
			std::cout << "cast successful" << std::endl;
	}

};

namespace RvalueLvalueSemantic
{
	
	class CopyableClass
	{
		std::string* member = nullptr;
		
		
		public:
		
			CopyableClass()
			{
				static int memberNum = 0;
				
				memberNum++;
				member = new std::string( "class instance " + std::to_string(memberNum) );
				
				std::cout << "CopyableClass()" << std::endl;
			};
			CopyableClass( const CopyableClass& copyable )
			{
				if ( copyable.member )
					member = new std::string( (*copyable.member) );
				
				std::cout << "CopyableClass( const CopyableClass& copyable )" << std::endl;
			};
			CopyableClass( CopyableClass&& copyable )
			{
				if ( copyable.member )
					member = copyable.member;
				
				copyable.member = nullptr;
				
				std::cout << "CopyableClass( CopyableClass&& copyable )" << std::endl;
			}
			//when use custom move-assign operator it's necessary use custom assign operator too
			//because when executing move semantics uniform-ref can call assign or move-assing operator
			CopyableClass& operator= ( const CopyableClass& copyable )
			{
				if ( member )
				{
					delete member;
					member = nullptr;
				}
				
				if ( copyable.member )
					member = new std::string( *copyable.member );
				
				
				std::cout << "operator= ( const CopyableClass& copyable )" << std::endl;
				
				return *this;
			}
			CopyableClass& operator= ( CopyableClass&& copyable )
			{
				if ( member )
				{
					delete member;
					member = nullptr;
				}
				
				if ( copyable.member )
					member = copyable.member;
				
				copyable.member = nullptr;
				
				std::cout << "operator= ( CopyableClass&& copyable )" << std::endl;
				
				return *this;
			}
			virtual ~CopyableClass()
			{
				delete member;
				member = nullptr;
				
				std::cout << "~CopyableClass()" << std::endl;
			};
		
			void showMember() const
			{
				if ( member )
					std::cout << (*member) << std::endl;
			}
	};
	
	CopyableClass returnLvalueFunc()
	{
		CopyableClass inst;
		return inst;
	}

	void example()
	{
		{
			CopyableClass instance;
			CopyableClass instance2( instance );
			CopyableClass instance3( std::move( CopyableClass() ) );
			
			instance.showMember();
			instance2.showMember();
			instance3.showMember();
		}
		
		{
			std::cout << "\n move in containers algorithms \n";
			
			std::vector<CopyableClass> movableCol;
			
			movableCol.resize( 2 );
			movableCol[ 0 ] = std::move( CopyableClass() );
			movableCol[ 1 ] = std::move( CopyableClass() );
			
			std::vector<CopyableClass> receivableCol;
			std::move( movableCol.begin(), movableCol.end(), std::inserter( receivableCol, receivableCol.begin() ) );
		}
		
		{
			std::cout << "\n move in const containers \n";
			
			 
			const std::vector<CopyableClass> movableConstCol = { CopyableClass(), CopyableClass() };
			
			std::vector<CopyableClass> receivableCol;
			std::move( movableConstCol.begin(), movableConstCol.end(), std::inserter( receivableCol, receivableCol.begin() ) );
		}
	}

}

int main()
{
	RTTIEmulation::example();

	std::cin.get();

	return 0;
}
