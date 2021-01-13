#include "ParallelProgramming.h"

#include "RecursiveLock.h"
#include "RecursiveLockResolve.h"
#include "ConditionVariables.h"

#include "CommonInclude.h"
#include <random>
#include <chrono>
#include <thread>
#include <atomic>

namespace ParallelProgramming
{
	void computingFunc( char id )
	{
		std::default_random_engine dre;//( std::chrono::system_clock::now().time_since_epoch().count() );
		std::uniform_int_distribution<int> di(10,500);

		for( int i = 0; i < 6; i++ )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( di(dre)) );
			std::cout << "computing \"" << id << "\"..." << std::endl;
		}

		std::cout << "\"" << id << "\" end computing" << std::endl;
	}

	void computingFuncWithReturnResultThrowPromise( char id, std::promise<int>& promise )
	{
		computingFunc( id );
		promise.set_value_at_thread_exit( (int)id );
	}


	void asyncAndFutureExample()
	{
		LOGOUT_FUNC

		{
			auto futureA = std::async( computingFunc, 'a' );
			auto futureB = std::async( std::launch::async, computingFunc, 'b' );
			auto futureC = std::async( std::launch::deferred, computingFunc, 'c' );
			auto futureD = std::async( std::launch::deferred, computingFunc, 'd' );
			auto futureE = std::async( std::launch::deferred, computingFunc, 'e' );
			auto futureF = std::shared_future<void>( std::async( std::launch::deferred, computingFunc, 'f' ) );
			auto futureG = std::async( std::launch::deferred, computingFunc, 'g' ).share();
			
			futureD.wait();
			futureE.get();
			futureF.get();
			futureG.get();


			if ( futureE.valid() )
			{
				futureE.get();
			}
			else
			{
				std::cout << "after call get() future seted in to invalid state" << std::endl;
			}

			if ( futureF.valid() && futureG.valid() )
			{
				std::cout << "but shared_future allow call get() more then one time" << std::endl;
				futureF.get();
				futureG.get();
			}
		}

		std::cout << "block finish" << std::endl;
		std::cout << std::endl;

		{
			auto futureP = std::async( std::launch::deferred, computingFunc, 'p' );
			auto futureQ = std::async( std::launch::deferred, computingFunc, 'q' );

			futureP.wait_for(std::chrono::microseconds(2));
			futureQ.wait_until( std::chrono::system_clock::now() + std::chrono::milliseconds( 100 ) );
		}

		std::cout << "block finish" << std::endl;
		std::cout << std::endl;
	}

	void threadAndPromiseExample()
	{
		LOGOUT_FUNC
		
		{
			std::promise<int> promise;
			std::thread thread1( computingFuncWithReturnResultThrowPromise, 'r', std::ref(promise) );
			auto futureR = promise.get_future().share();
			thread1.detach();

			std::thread thread2( computingFunc, 's' );
			thread2.detach();

			futureR.get();
			if ( futureR.valid() )
			{
				std::cout << "futureR = " << futureR.get() << std::endl;
			}

			std::thread thread3( computingFunc, 'n' );
			thread3.join();

			std::thread thread4( computingFunc, 't' );
			thread4.detach();
		}
		std::cout << "block finish" << std::endl;
		std::cout << std::endl;
	}

	void packagedTaskExample()
	{
		LOGOUT_FUNC

		std::packaged_task<void(char)> task( computingFunc );

		auto futureV = task.get_future();

		auto futureU = std::async( [&task](){ computingFunc( 'u' ); task( 'v' ); } );

		computingFunc( 'w' );

		futureV.get();
	}

	void mutexAndLocksFailExample()
	{
		LOGOUT_FUNC

		std::chrono::nanoseconds computingTime{0};
		std::mutex computingTimeLock;

		auto task = [&](char id)
		{
			auto startComputingTime = std::chrono::system_clock::now();	
			computingFunc( id );
			auto coputingTime = std::chrono::system_clock::now() - startComputingTime;

			computingTimeLock.lock();
			computingTime += std::chrono::duration_cast<std::chrono::nanoseconds>( coputingTime );
			std::cout << "alarm deadlock, there is no unlock for this lock" << std::endl;
		};

		auto taskWithExeption = [&](char id)
		{
			try
			{
				auto startComputingTime = std::chrono::system_clock::now();	
				computingFunc( id );
				auto coputingTime = std::chrono::system_clock::now() - startComputingTime;

				computingTimeLock.lock();
				computingTime += std::chrono::duration_cast<std::chrono::nanoseconds>( coputingTime );
			
				throw std::bad_exception();

				computingTimeLock.unlock();
			}
			catch ( std::bad_exception )
			{
				std::cout << "alarm deadlock, after throw exeption block never reached unlock operation" << std::endl;
			}
		};

		std::thread thread1( task, 'a' );
		std::thread thread2( taskWithExeption, 'b' );

		task( 'c' );

		thread1.join();
		thread2.join();
	}

	void mutexAndLocksExample()
	{
		LOGOUT_FUNC

		std::chrono::nanoseconds computingTime{0};
		std::mutex computingTimeLock;

		auto task = [&](char id)
		{
			auto startComputingTime = std::chrono::system_clock::now();	
			computingFunc( id );
			auto coputingTime = std::chrono::system_clock::now() - startComputingTime;

			std::scoped_lock<std::mutex> locker(computingTimeLock);
			computingTime += std::chrono::duration_cast<std::chrono::nanoseconds>( coputingTime );
		};

		auto taskWithExeption = [&](char id)
		{
			try
			{
				auto startComputingTime = std::chrono::system_clock::now();	
				computingFunc( id );
				auto coputingTime = std::chrono::system_clock::now() - startComputingTime;

				std::scoped_lock<std::mutex> locker( computingTimeLock );
				computingTime += std::chrono::duration_cast<std::chrono::nanoseconds>( coputingTime );
			
				throw std::bad_exception();
			}
			catch ( std::bad_exception )
			{
				
			}
		};

		std::thread thread1( task, 'a' );
		std::thread thread2( task, 'b' );

		task( 'c' );

		thread1.join();
		thread2.join();
	}

	void recursiveLockExample()
	{
		auto recursiveLockTask = [](int term)
		{
			RecursiveLock recuresiveLock;
			recuresiveLock.addToData( term );

			std::cout << "recuresiveLock data = " << recuresiveLock.getData() << std::endl;
		};

		//std::thread recursiveLockThread( recursiveLockTask, 5 );
		//recursiveLockThread.detach();

		auto recursiveLockResolveTask = [](int term)
		{
			RecursiveLockResolve recuresiveLockResolve;
			recuresiveLockResolve.addToData( term );

			std::cout << "recuresiveLockResolve data = " << recuresiveLockResolve.getData() << std::endl;
		};

		std::thread recursiveLockResolveThread( recursiveLockResolveTask, 5 );
		recursiveLockResolveThread.detach();
	}

	void callOnceExample()
	{
		std::once_flag initOnce;

		auto initializer = [](int id)
		{
			std::cout << id << " initilizer runed" << std::endl;
		};

		std::call_once( initOnce, initializer, 1 );
		std::call_once( initOnce, initializer, 2 );
	}

	void conditionVariableExample()
	{
		ConditionVariables example;
		std::cin.get();
	}

}