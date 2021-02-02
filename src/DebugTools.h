#ifndef DebugTools_H
#define DebugTools_H

#include "CommonInclude.h"
#include <random>

namespace DebugTools
{
	void example()
	{
		std::default_random_engine dre;
		std::uniform_real_distribution<float> df(0.0f, 1.01f);

		float* arr = new float[10000];

		for( int indx = 0; indx < 10000; indx++ )
		{
			float logoutValueIfMoreThen0_95 = df(dre);
			arr[indx] = logoutValueIfMoreThen0_95;

			bool hitBraeakPointIfIndxEqual40 = true;
		}

		delete[] arr;

		LOGOUT_FUNC
	}
};

#endif