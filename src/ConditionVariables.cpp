#include "ConditionVariables.h"

#include "CommonInclude.h"

#include <functional>
#include <random>


namespace ParallelProgramming
{

	ConditionVariables::ConditionVariables()
	{
		LOGOUT_FUNC

		std::atomic_init(&_finishThreads, false );

		_addDataThread = new std::thread( std::bind( &ConditionVariables::addData, this ) );

		for( int i = 0; i < 3; i++ )
		{
			auto thread = new std::thread( std::bind( &ConditionVariables::computingData, this ) );
			_computingThreads.push_back( thread );
		}
	}

	ConditionVariables::~ConditionVariables()
	{
		_finishThreads.store( true );


		if ( _addDataThread && _addDataThread->joinable() )
		{
			_addDataThread->join();
			delete _addDataThread;
			_addDataThread = nullptr;
		}

		_existUncomputingData.notify_all();

		for( auto thread : _computingThreads )
		{
			if( thread->joinable() )
			{
				thread->join();
				delete thread;
			}
		}
		_computingThreads.clear();

		std::cout << "Computing finished" << std::endl;

	}


	void ConditionVariables::addData()
	{
		std::unique_lock<std::mutex> dataLock(_dataLocker, std::defer_lock );
		std::default_random_engine dre;
		std::uniform_int_distribution<int> di(3000,4000);

		while( !_finishThreads.load() )
		{
			int dataAmount = 3;
			dataLock.lock();
			for( int i = 0; i < dataAmount; i++ )
			{
				_data.push_back( di(dre) );
			}
			dataLock.unlock();

			_existUncomputingData.notify_all();

			std::cout << "addData thread " << std::this_thread::get_id() << " work" << std::endl;
			std::cout << "Press Enter if you want stop generation" << std::endl;
			std::this_thread::sleep_for( std::chrono::milliseconds(di(dre)));
		}
	}

	void ConditionVariables::computingData()
	{
		std::unique_lock<std::mutex> dataLock( _dataLocker, std::defer_lock );
		std::mutex conditionWait;
		std::default_random_engine dre;
		std::uniform_int_distribution<int> di(1000,1500);

		while( !_finishThreads.load() )
		{
			bool isExistData = false;
			int newData = 0;

			dataLock.lock();
			if ( !_data.empty() )
			{
				newData = _data.back();
				_data.pop_back();
				isExistData = true;
			}
			dataLock.unlock();

			if ( isExistData )
			{
				std::cout << "computingData thread " << std::this_thread::get_id() << " work" << std::endl;
				std::this_thread::sleep_for( std::chrono::microseconds(newData));
			}
			else
			{
				std::cout << "computingData thread " << std::this_thread::get_id() << " wait..." << std::endl;
				std::unique_lock<std::mutex> conditionWaitLock(conditionWait);
				_existUncomputingData.wait(conditionWaitLock);
			}
		}
	}
}