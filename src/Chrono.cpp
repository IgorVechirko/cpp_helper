#include "Chrono.h"

#include "CommonInclude.h"
#include <chrono>
#include <ctime>

template< typename V, typename R>
std::ostream& operator << ( std::ostream& stream, const std::chrono::duration<V,R> duration )
{
	stream << "[" << duration.count() << " of " << R::num << "/" << R::den << "]";

	return stream;
}

namespace Chrono
{
	std::string getTimePointAsString( const std::chrono::system_clock::time_point& point )
	{
		auto time = std::chrono::system_clock::to_time_t(point);
		std::string str  = std::ctime( &time );

		if ( !str.empty() )
		{
			str.resize( str.size() - 1 );
		}

		return str;
	}

	void example()
	{
		{
			std::chrono::duration<int,std::ratio<1>> second{1};
			std::chrono::duration<int,std::ratio<20>> twentySeconds{1};
			std::chrono::duration<float,std::ratio<30,1>> halfMinute{1};
			std::chrono::duration<float,std::ratio<1,3>> thirdSecond{1};

			auto addResult = twentySeconds + halfMinute;
			std::cout << "addResult = " << addResult << std::endl;

			auto devideResult = second / thirdSecond;
			std::cout << "devideResult = " << devideResult << std::endl;

			if ( second == (thirdSecond*3) )
			{
				std::cout << "seconds == (thirdSecond*3)" << std::endl;
			}

			std::chrono::seconds imlicitCast = second;
			//std::chrono::hours ilegalImlicitCast = second; implicit cast to type with lower precision forbided
			auto explicitCast = std::chrono::duration_cast<std::chrono::hours>(second);

			std::cout << std::endl;
		}

		{
			std::chrono::system_clock::time_point epochTimePoint;
			std::cout << "system lock epoch: " << getTimePointAsString( epochTimePoint ) << std::endl;

			auto nowTimePoint = std::chrono::system_clock::now();
			auto timeSinceEpoch = nowTimePoint - epochTimePoint;
			std::cout << "now: " << getTimePointAsString( nowTimePoint ) << std::endl;

			std::cout << "periof from epoch: " << std::chrono::duration_cast<std::chrono::hours>(timeSinceEpoch ) << std::endl;
		}

	} 

}