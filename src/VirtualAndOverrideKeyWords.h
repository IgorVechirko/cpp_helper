#ifndef VirtualAndOverrideKeyWords_H
#define VirtualAndOverrideKeyWords_H

#include "CommonInclude.h"

namespace VirtualAndOverrideKeyWords
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

#endif