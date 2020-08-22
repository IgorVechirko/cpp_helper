#ifndef Random_H
#define Random_H

#include "CommonInclude.h"
#include <random>

namespace Random
{
	void example()
	{
		{
			std::default_random_engine dre;

			std::uniform_int_distribution<int> di{10,20};
			for( int i = 0; i < 20; i++ )
				std::cout << i << ". \t" << di(dre) << std::endl;

			std::cout << std::endl;

			std::uniform_real_distribution<float> df{10.0f, 20.0f};
			for( int i = 0; i < 20; i++ )
				std::cout << i << ". \t" << df(dre) << std::endl;

			std::cout << std::endl;


			std::vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			std::shuffle( coll.begin(), coll.end(), dre );

			std::cout << "shuffled coll: ";
			for( auto num : coll )
				std::cout << num << " ";
			std::cout << std::endl;
			std::cout << std::endl;
		}

		{
			std::default_random_engine dre1;
			std::default_random_engine dre2;

			std::uniform_int_distribution<int> di{10,20};

			if( di(dre1) == di(dre2) )
			{
				std::cout << "engine first initialized value not random, it predefined" << std::endl;
			}

			std::cout << std::endl;
		}

		{
			int randomInitilizer = 2;
			std::default_random_engine dre1(randomInitilizer);
			std::default_random_engine dre2(randomInitilizer);
			dre2.seed( randomInitilizer*2 );

			std::uniform_int_distribution<int> di{10,20};

			if( di(dre1) != di(dre2) )
			{
				std::cout << "engine first initialized value can be setup in constructor or throw seed method" << std::endl;
			}

			dre1.seed( 2 );

			std::cout << std::endl;
		}
	}

}


#endif