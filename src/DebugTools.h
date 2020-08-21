#ifndef DebugTools_H
#define DebugTools_H

#include "CommonInclude.h"
#include <ctime>

namespace DebugTools
{
	void example()
	{
		float arr[10000];

		srand(time(nullptr));

		for( int indx = 0; indx < 10000; indx++ )
		{
			float logoutValueIfMoreThen0_95 = (float)rand() / (float)RAND_MAX;
			arr[indx] = logoutValueIfMoreThen0_95;
		}

		LOGOUT_FUNC
	}
};

#endif