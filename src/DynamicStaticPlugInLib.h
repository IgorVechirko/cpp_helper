#ifndef DynamicStaticPlugInLib_H
#define DynamicStaticPlugInLib_H

#include <Windows.h>

#ifdef DYNAMIC_LIB_EXPORT
	#define DYNAMIC_LIB_API __declspec(dllexport)
#else
	#define DYNAMIC_LIB_API __declspec(dllimport)
#endif




namespace DynamicStaticPlugInLib
{
	void DYNAMIC_LIB_API function();

	class DYNAMIC_LIB_API LibClass
	{
		public:

			void method();

	};
}


#endif
