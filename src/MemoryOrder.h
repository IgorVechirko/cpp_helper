#ifndef MemoryOrder_H
#define MemoryOrder_H

#include <string>
#include <atomic>

namespace MemoryOrder
{

struct TestCtx
{
	std::atomic<bool> m_first{false};
	std::atomic<bool> m_second{false};

	std::atomic<uint32_t> m_allSetCount{0};
};

class SequenceConsistency
{

public:

	void sample();

private:

	static void setFirst(TestCtx& _ctx);
	static void setSecond(TestCtx& _ctx);

	static void readFirstThenSecond(TestCtx& _ctx);

	static void readSecondThenFirst(TestCtx& _ctx);

	static void runTest();

private:


};

class OrderRelaxed
{
public:

	void sample();

private:

	static void writeFirst(TestCtx& _ctx);
	static void writeSecond(TestCtx& _ctx);
	static void readSecondThenFirst(TestCtx& _ctx);

	static void runTest();

	
};

class AcquirReleaseOrder
{
public:

	void sample();

private:

	static void writeFirsThenSecond(TestCtx& _ctx);
	static void readSecondThenFirst(TestCtx& _ctx);

	static void runTest();
};

class ConsumeReleaseOrder
{

public:

	void sample();

private:

	static void writeOperation(TestCtx& _ctx, std::atomic<bool>& _relaxedFlag);
	static void readOperation(TestCtx& _ctx, std::atomic<bool>& _relaxedFlag);

	static void runTest();
};

}

#endif