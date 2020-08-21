#ifndef RTTIEmulation_H
#define RTTIEmulation_H

#include "CommonInclude.h"
#include <vector>

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

#endif