#ifndef ConditionVariables_H
#define ConditionVariables_H



#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

namespace ParallelProgramming
{

	class ConditionVariables
	{
		std::vector<std::thread*> _computingThreads;
		std::thread* _addDataThread{nullptr};

		std::atomic<bool> _finishThreads{false};

		std::vector<int> _data;
		std::mutex _dataLocker;

		std::condition_variable _existUncomputingData;

	public:

		ConditionVariables();

		virtual ~ConditionVariables();

		void addData();

		void computingData();
	};

};


#endif