#pragma once


#include <mutex>
#include <memory>
#include <functional>

template<typename T>
class ParallelList
{

	struct Node
	{
		std::mutex _lock;
		std::shared_ptr<T> _data;
		std::unique_ptr<Node> _next;

		Node()
		{}

		Node(const T& value)
			: _data(std::make_shared<T>(value))
		{
		}
	};

	Node _head;

public:

	ParallelList()
	{}
	~ParallelList()
	{
		//removeIf([](T&)->bool{return true;});
	}

	ParallelList(const ParallelList&) = delete;
	ParallelList& operator=(const ParallelList&) = delete;

	void pushFront(const T& value)
	{
		auto newNode = std::make_unique<Node>(value);
		std::unique_lock lock(_head._lock);
		newNode->_next = std::move(_head._next);
		_head._next = std::move(newNode);
	}

	void forEach(std::function<void(T&)> func)
	{
		auto current = &_head;
		std::unique_lock currentLock(current->_lock);
		while(auto next = current->_next.get())
		{
			std::unique_lock nextLock(next->_lock);
			currentLock.unlock();
			func(*(next->_data.get()));
			current = next;
			currentLock = std::move(nextLock);
		}
	}

	std::shared_ptr<T> findFirstIf(std::function<bool(T&)> func)
	{
		auto current = &_head;
		std::unique_lock currentLock(current->_lock);
		while(auto next = current->_next.get())
		{
			std::unique_lock nextLock(next->_lock);
			currentLock.unlock();
			if(func(*(next->_data.get())))
			{
				return next->_data;
			}

			current = next;
			currentLock = std::move(nextLock);
		}

		return nullptr;
	}

	void removeIf(std::function<bool(T&)> func)
	{
		auto current = &_head;
		std::unique_lock currentLock(current->_lock);
		while(auto next = current->_next.get())
		{
			std::unique_lock nextLock(next->_lock);
			
			if(func(*(next->_data.get())))
			{
				auto oldNext = std::move(current->_next);
				current->_next = std::move(oldNext->_next);
				nextLock.unlock();
			}
			else
			{
				currentLock.unlock();
				current = next;
				currentLock = std::move(nextLock);
			}
		}
	}
};