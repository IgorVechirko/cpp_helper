#include "SmartPointers.h"


namespace SmartPointers
{
	//TestClass		
	TestClass::TestClass()
	{
		LOGOUT_FUNC
	}
	TestClass::~TestClass()
	{
		LOGOUT_FUNC
	}


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

	

	//SharedPtrCycleRelation
	SharedPtrCycleRelation::SharedPtrCycleRelation()
	{
		LOGOUT_FUNC

		std::vector<std::string> persons = { "person1", "person2", "person3", "person4" };
		std::vector<std::string> casts = { "casta1", "casta2", "casta3", "casta4" };

		for( const auto& person : persons )
			humans.push_back( std::shared_ptr<sHuman>( new sHuman{ person } ) );

		for( const auto& casta : casts )
			groups.push_back( std::shared_ptr<sGroup>( new sGroup{ casta } ) );

		for( auto& humanPtr : humans )
			humanPtr->groups = groups;

		for( auto& groupPtr : groups )
			groupPtr->humans = humans;

	}
	SharedPtrCycleRelation::~SharedPtrCycleRelation()
	{
		LOGOUT_FUNC
	}


	//ResolveSharedPtrCycleRelationWithWeakPtr
	ResolveSharedPtrCycleRelationWithWeakPtr::ResolveSharedPtrCycleRelationWithWeakPtr()
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
	ResolveSharedPtrCycleRelationWithWeakPtr::~ResolveSharedPtrCycleRelationWithWeakPtr()
	{
		LOGOUT_FUNC
	}

	//UniquePtrTest
	UniquePtrTest::UniquePtrTest()
	{
		LOGOUT_FUNC
	}
	UniquePtrTest::~UniquePtrTest()
	{
		LOGOUT_FUNC
	}


	//Allocator
	void* Allocator::allocate( size_t size )
	{
		LOGOUT_FUNC

		return new char[size];
	}
	void Allocator::deallocate( void* ptr ) const
	{
		LOGOUT_FUNC

		delete[] ptr;
	}


	void example()
	{
		{
			SharedPtrCycleRelation sharedPtrCycleRelation;
		}

		std::cout << std::endl << std::endl;

		{
			ResolveSharedPtrCycleRelationWithWeakPtr resolveSharedPtrCycleRelationWithWeakPtr;
		}

		std::cout << std::endl << std::endl;

		{
			Allocator allocator;
			auto testInstance = new( allocator.allocate(sizeof(UniquePtrTest)) ) UniquePtrTest();
			auto uniquePtr = std::unique_ptr<UniquePtrTest,Allocator&>(testInstance, allocator );

		}
	}

};