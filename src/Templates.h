#ifndef Templates_H
#define Templates_H

#include "CommonInclude.h"

namespace Templates
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

	class BaseClass
	{
		bool _isInited{false};
		std::string _className = "BaseClass";


	protected:

		void setupClassName( const std::string& className )
		{
			_className = className;
		}

	public:

		void init()
		{
			_isInited = true;
		}

		void startUse()
		{
			if(_isInited)
			{
				std::cout << _className << " instance start used" << std::endl;
			}
		}

	};

	class ChildClass : public BaseClass
	{
		public:

			void ininWithClassName( const std::string& className )
			{
				setupClassName( "ChildClass" );
			}
	};


	template< typename ObjType, typename InitializerType, typename... InitArgsTypes >
	ObjType* createWithInitializer( InitializerType initializerPtr, const InitArgsTypes... initArgs )
	{
		ObjType* ret = new(std::nothrow) ObjType();
		
		if ( ret )
		{
			ret->init();

			if( initializerPtr )
			{
				(ret->*initializerPtr)( initArgs...);
			}
		}
		else
		{
			delete ret;
			ret = nullptr;
		}

		return ret;
	}


	void example()
	{
		tempalteFunctionWithTypesPackage( "", 5, 0.054f, true );
		tempalteFunctionWithTypesPackage( 5, 0.054, true );

		auto customCreatedObj = new ChildClass();
		customCreatedObj->ininWithClassName( "ChildClass" );

		auto templateFuncCreatedObj = createWithInitializer<ChildClass>(&ChildClass::ininWithClassName, "ChildClass" );

		customCreatedObj->startUse();
		templateFuncCreatedObj->startUse();
	}
	

	//template alias
	template< typename T>
	class MyAllocator
	{
	};

	template<typename T>
	using MyVec = std::vector<T,MyAllocator<T>>;

};

#endif