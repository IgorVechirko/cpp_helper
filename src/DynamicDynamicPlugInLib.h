#ifndef DynamicDynamicPlugInLib_H
#define DynamicDynamicPlugInLib_H

#include <Windows.h>


#define DYNAMIC_LIB_API extern "C" __declspec(dllexport)


DYNAMIC_LIB_API int CALLBACK function( char* str);



#endif
