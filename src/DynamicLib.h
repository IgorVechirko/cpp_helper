#ifndef DynamicLib_H
#define DynamicLib_H

#ifdef _WINDOWS

#ifdef DYNAMIC_LIB_EXPORT
	#define DYNAMIC_LIB_API __declspec(dllexport)
#else
	#define DYNAMIC_LIB_API __declspec(dllimport)
#endif

#else
	#define DYNAMIC_LIB_API
#endif


namespace DynamicLib
{
	void DYNAMIC_LIB_API function();

	class DYNAMIC_LIB_API LibClass
	{
		public:

			void method();

	};
}


#endif
