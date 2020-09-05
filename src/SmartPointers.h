#ifndef SmartPointers_H
#define SmartPointers_H

#include "CommonInclude.h"
#include <vector>

namespace SmartPointers
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

	class UniquePtrTest
	{
		int someMember = 0;

	public:

		UniquePtrTest()
		{
			LOGOUT_FUNC
		}
		virtual ~UniquePtrTest()
		{
			LOGOUT_FUNC
		}

	};

	class Allocator
	{

	public:

		void* allocate( size_t size )
		{
			LOGOUT_FUNC

			return new char[size];
		}
		void deallocate( void* ptr ) const
		{
			LOGOUT_FUNC

			delete[] ptr;
		}

		template< typename T>
		void operator() (T* ptr) const
		{
			LOGOUT_FUNC
			ptr->~UniquePtrTest();
			deallocate( ptr );
		}

	};


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
			auto uniquePtr = std::unique_ptr<UniquePtrTest, Allocator>(testInstance);

		}
	}

};


#endif
