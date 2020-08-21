#ifndef MemoryAllocations_H
#define MemoryAllocations_H

#include "CommonInclude.h"

void* operator new ( std::size_t count )
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
}


namespace MemoryAllocations
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

#endif