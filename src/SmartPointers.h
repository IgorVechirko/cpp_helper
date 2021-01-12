#ifndef SmartPointers_H
#define SmartPointers_H

#include "CommonInclude.h"
#include <vector>

namespace SmartPointers
{
	class TestClass
	{
		public:
				
			TestClass();
			virtual ~TestClass();

	};

	void sharedPtrExample();
	void uniquePtrExample();


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

			SharedPtrCycleRelation();
			virtual ~SharedPtrCycleRelation();
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

			ResolveSharedPtrCycleRelationWithWeakPtr();
			virtual ~ResolveSharedPtrCycleRelationWithWeakPtr();
	};

	class UniquePtrTest
	{
		int someMember = 0;

	public:

		UniquePtrTest();
		virtual ~UniquePtrTest();

	};

	class Allocator
	{

	public:

		void* allocate( size_t size );
		void deallocate( void* ptr ) const;

		template< typename T>
		void operator() (T* ptr) const
		{
			LOGOUT_FUNC
			ptr->~UniquePtrTest();
			deallocate( ptr );
		}

	};


	void example();

};


#endif
