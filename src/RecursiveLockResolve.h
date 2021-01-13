#ifndef RecursiveLockResolve_H
#define RecursiveLockResolve_H

#include <mutex>

namespace ParallelProgramming
{
	class RecursiveLockResolve
	{
		int _data{0};
		std::recursive_mutex _dataLocker;

	public:

		int getData()
		{
			int result = 0;

			std::unique_lock<std::recursive_mutex> lock(_dataLocker,std::defer_lock);
			lock.lock();
			result = _data;
			lock.unlock();

			return result;
		}

		void addToData( int term )
		{
			std::scoped_lock<std::recursive_mutex> lock(_dataLocker);
			_data = getData() + term;
		}

	};
};


#endif