#ifndef MemoryOrder_H
#define MemoryOrder_H

#include <atomic>

namespace MemoryOrder
{

	struct TestCtx
{
	std::atomic<bool> m_first;
	std::atomic<bool> m_second;

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

}

#endif