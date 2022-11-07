#pragma once

#include <mutex>
#include <memory>

template<typename T>
class ParallelQueue
{

private:

	struct Node
	{
		std::shared_ptr<T> _data;
		std::unique_ptr<Node> _next;
	};

private:

	Node* getTail() const
	{
		std::unique_lock lock(_tailLock);
		return _tail;
	}

	std::unique_ptr<Node> popHead()
	{
		std::unique_lock lock(_headLock);

		if(_head.get() == getTail())
		{
			return nullptr;
		}

		std::unique_ptr<Node> ret(std::move(_head));
		_head = std::move(ret->_next);
		
		return ret;
	}

	std::unique_lock<std::mutex> waitData()
	{
		std::unique_lock lock(_headLock);
		_dataCond.wait(lock, [&](){return _head.get() != getTail();});
		return std::move(lock);
	}

public:

	ParallelQueue()
		: _head(new Node())
		, _tail(_head.get())
	{
	}
	ParallelQueue(const ParallelQueue& queue) = delete;
	ParallelQueue& operator=(const ParallelQueue& queue) = delete;

	void push(const T& value)
	{
		auto newTail = std::make_unique<Node>();
		auto newData = std::make_shared<T>(value);

		{
			std::unique_lock lock(_tailLock);

			_tail->_data = newData;
			_tail->_next = std::move(newTail);
			_tail = _tail->_next.get();
		}

		_dataCond.notify_one();
	}

	std::shared_ptr<T> tryPop()
	{
		auto oldHead = popHead();
		return oldHead ? oldHead->_data : nullptr;
	}

	bool tryPop(T& value)
	{
		auto oldHead = popHead();

		if(oldHead)
		{
			value = std::move(*oldHead->_data);
			return true;
		}

		return false;
	}

	std::shared_ptr<T> waitAndPop()
	{
		std::unique_lock lock(waitData());

		std::unique_ptr<Node> oldHead(std::move(_head));
		_head = std::move(oldHead->_next);
		
		return oldHead->_data;
	}

	void waitAndPop(T& value)
	{
		std::unique_ptr<Node> oldHead;

		{
			std::unique_lock lock(waitData());

			oldHead = std::move(_head);
			_head = std::move(oldHead->_next);
		}

		value = std::move(*oldHead->_data);
	}

	bool empty() const
	{
		std::unique_lock lock(_headLock);

		return _head == getTail();
	}


private:

	mutable std::mutex _headLock;
	std::unique_ptr<Node> _head;

	mutable std::mutex _tailLock;
	Node* _tail{nullptr};

	std::condition_variable _dataCond;

};