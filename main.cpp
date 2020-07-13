#include <iostream>
#include <vector>
#include <string>

#define OUT_FUNC std::cout << __FUNCTION__ << std::endl;

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
				std::cout << __FUNCTION__ << std::endl;
			}
			
			virtual ~TestClass()
			{
				std::cout << __FUNCTION__ << std::endl;
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
				OUT_FUNC
			}
			~sHuman()
			{
				OUT_FUNC
			}
		};

		struct sGroup
		{
			std::string name;
			std::vector<std::shared_ptr<sHuman>> humans;

			sGroup( const std::string& name )
			{
				this->name = name;
				OUT_FUNC
			}
			~sGroup()
			{
				OUT_FUNC
			}
		};

		std::vector<std::shared_ptr<sHuman>> humans;
		std::vector<std::shared_ptr<sGroup>> groups;

		public:

			SharedPtrCycleRelation()
			{
				OUT_FUNC

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
				OUT_FUNC
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
				OUT_FUNC
			}
			~sHuman()
			{
				OUT_FUNC
			}
		};

		struct sGroup
		{
			std::string name;
			std::vector<std::weak_ptr<sHuman>> humans;

			sGroup( const std::string& name )
			{
				this->name = name;
				OUT_FUNC
			}
			~sGroup()
			{
				OUT_FUNC
			}
		};

		std::vector<std::shared_ptr<sHuman>> humans;
		std::vector<std::shared_ptr<sGroup>> groups;

		public:

			ResolveSharedPtrCycleRelationWithWeakPtr()
			{
				OUT_FUNC

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
				OUT_FUNC
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


int main()
{

	std::cin.get();

	return 0;
}
