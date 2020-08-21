#ifndef FinalKeyWord_H
#define FinalKeyWord_H

#include "CommonInclude.h"


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


#endif