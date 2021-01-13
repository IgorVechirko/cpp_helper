#ifndef RecursiveLock_H
#define RecurciveLock_H

#include <mutex>

namespace ParallelProgramming
{
	class RecursiveLock
	{
		int _data{0};
		std::mutex _dataLocker;

	public:

		int getData()
		{
			int result = 0;

			std::unique_lock<std::mutex> lock(_dataLocker,std::defer_lock);
			lock.lock();
			result = _data;
			lock.unlock();

			return result;
		}

		void addToData( int term )
		{
			std::scoped_lock<std::mutex> lock(_dataLocker);
			_data = getData() + term;
		}

	};
};



#endif