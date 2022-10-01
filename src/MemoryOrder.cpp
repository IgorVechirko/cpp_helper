#include "MemoryOrder.h"

#include <thread>
#include <vector>
#include "CommonInclude.h"

namespace MemoryOrder
{

//SequenceConsistency
void SequenceConsistency::setFirst(TestCtx& _ctx)
{
	_ctx.m_first.store(true, std::memory_order_seq_cst);
}

void SequenceConsistency::setSecond(TestCtx& _ctx)
{
	_ctx.m_second.store(true, std::memory_order_seq_cst);
}
void SequenceConsistency::readFirstThenSecond(TestCtx& _ctx)
{
	while(!_ctx.m_first.load(std::memory_order_seq_cst));

	if(_ctx.m_second.load(std::memory_order_seq_cst))
		++_ctx.m_allSetCount;
}
void SequenceConsistency::readSecondThenFirst(TestCtx& _ctx)
{
	while(!_ctx.m_second.load(std::memory_order_seq_cst));

	if(_ctx.m_first.load(std::memory_order_seq_cst))
		++_ctx.m_allSetCount;
}
void SequenceConsistency::runTest()
{
	TestCtx ctx;

	auto thread1 = std::make_unique<std::thread>(setFirst, std::ref(ctx));
	auto thread2 = std::make_unique<std::thread>(setSecond, std::ref(ctx));
	auto thread3 = std::make_unique<std::thread>(readFirstThenSecond, std::ref(ctx));
	auto thread4 = std::make_unique<std::thread>(readSecondThenFirst, std::ref(ctx));

	thread1->join();
	thread2->join();
	thread3->join();
	thread4->join();

	if(!ctx.m_allSetCount)
	{
		std::cout << "It's never happend" << std::endl;
	}
}

void SequenceConsistency::sample()
{
	//std::vector<std::thread> samples;
	for(int i = 0; i< 1000; ++i)
	{
		std::thread thread(runTest);
		thread.join();
	}

	//for(auto& thread : samples)
	//	thread.join();

	std::cout << "Test finish" << std::endl;
}




//OrderRelaxed
void OrderRelaxed::writeFirst(TestCtx& _ctx)
{
	_ctx.m_first.store(true, std::memory_order_relaxed);
}
void OrderRelaxed::writeSecond(TestCtx& _ctx)
{
	_ctx.m_second.store(true, std::memory_order_relaxed);
}
void OrderRelaxed::readSecondThenFirst(TestCtx& _ctx)
{
	while(!_ctx.m_second.load(std::memory_order_relaxed));

	if(_ctx.m_first.load(std::memory_order_relaxed))
		++_ctx.m_allSetCount;
}
void OrderRelaxed::runTest()
{
	TestCtx ctx;

	auto thread1 = std::make_unique<std::thread>(writeFirst, std::ref(ctx));
	auto thread2 = std::make_unique<std::thread>(writeSecond, std::ref(ctx));
	auto thread3 = std::make_unique<std::thread>(readSecondThenFirst, std::ref(ctx));

	thread1->join();
	thread2->join();
	thread3->join();

	if(!ctx.m_allSetCount)
	{
		std::cout << "It's could happend" << std::endl;
	}
}
void OrderRelaxed::sample()
{
	//std::vector<std::thread> samples;
	for(int i = 0; i< 100; ++i)
	{
		std::thread thread(runTest);
		thread.join();
	}

	//for(auto& thread : samples)
	//	thread.join();

	std::cout << "Test finish" << std::endl;
}




//AcquirReleaseOrder
void AcquirReleaseOrder::writeFirsThenSecond(TestCtx& _ctx)
{
	_ctx.m_first.store(true, std::memory_order_relaxed);
	_ctx.m_second.store(true, std::memory_order_release);
}
void AcquirReleaseOrder::readSecondThenFirst(TestCtx& _ctx)
{
	while(!_ctx.m_second.load(std::memory_order_acquire));

	if(_ctx.m_first.load(std::memory_order_relaxed))
		++_ctx.m_allSetCount;
}
void AcquirReleaseOrder::runTest()
{
	TestCtx ctx;

	auto thread1 = std::make_unique<std::thread>(writeFirsThenSecond, std::ref(ctx));
	auto thread2 = std::make_unique<std::thread>(readSecondThenFirst, std::ref(ctx));

	thread1->join();
	thread2->join();

	if(!ctx.m_allSetCount)
	{
		std::cout << "It's never happend" << std::endl;
	}
}
void AcquirReleaseOrder::sample()
{
	//std::vector<std::thread> samples;
	for(int i = 0; i< 100; ++i)
	{
		std::thread thread(runTest);
		thread.join();
	}

	//for(auto& thread : samples)
	//	thread.join();

	std::cout << "Test finish" << std::endl;
}



//ConsumeReleaseOrder
void ConsumeReleaseOrder::writeOperation(TestCtx& _ctx, std::atomic<bool>& _relaxedFlag)
{
	_relaxedFlag.store(true, std::memory_order_relaxed);

	_ctx.m_second.store(true, std::memory_order_relaxed);
	_ctx.m_first.store(true, std::memory_order_release);
}
void ConsumeReleaseOrder::readOperation(TestCtx& _ctx, std::atomic<bool>& _relaxedFlag)
{
	while(!_ctx.m_first.load(std::memory_order_consume));

	if(_ctx.m_second.load(std::memory_order_relaxed) &&
		_relaxedFlag.load(std::memory_order_relaxed))
	{
		++_ctx.m_allSetCount;
	}
}
void ConsumeReleaseOrder::runTest()
{
	std::atomic<bool> relaxedFlag{false};
	TestCtx ctx;

	auto thread1 = std::make_unique<std::thread>(writeOperation, std::ref(ctx), std::ref(relaxedFlag));
	auto thread2 = std::make_unique<std::thread>(readOperation, std::ref(ctx), std::ref(relaxedFlag));

	thread1->join();
	thread2->join();

	if(!ctx.m_allSetCount)
	{
		std::cout << "It's could happend" << std::endl;
	}
}
void ConsumeReleaseOrder::sample()
{
	//std::vector<std::thread> samples;
	for(int i = 0; i< 10000; ++i)
	{
		std::thread thread(runTest);
		thread.join();
	}

	//for(auto& thread : samples)
	//	thread.join();

	std::cout << "Test finish" << std::endl;
}

}
