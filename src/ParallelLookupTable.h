#pragma once

#include <mutex>
#include <memory>
#include <shared_mutex>
#include <list>
#include <vector>
#include <map>

template<typename Key, 
		typename Value,
		typename Hash = std::hash<Key>>
class ParallelLookupTable
{

	class BucketType
	{

		typedef std::pair<Key, Value> BucketValue;
		typedef std::list<BucketValue> BucketData;
		typedef typename BucketData::iterator BucketIterator;

	public:

		BucketData _data;
		std::shared_mutex _dataLock;

	private:

		BucketIterator findEntry(const Key& key)
		{
			return std::find_if(_data.begin(), _data.end(), [&](const BucketValue& entry)
				{
					return entry.first == key;
				});
		}

	public:

		Value getValue(const Key& key, const Value& defaultValue)
		{
			std::shared_lock lock(_dataLock);

			auto entryIt = findEntry(key);
			return entryIt == _data.end() ? defaultValue : entryIt->second;
		}

		void addOrUpdate(const Key& key, const Value& value)
		{
			std::unique_lock lock(_dataLock);

			auto entryIt = findEntry(key);
			if(entryIt == _data.end())
			{
				_data.push_back(BucketValue(key, value));
			}
			else
			{
				entryIt->second = value;
			}
		}

		void remove(const Key& key)
		{
			std::unique_lock lock(_dataLock);

			auto entryIt = findEntry(key);
			if(entryIt != _data.end())
			{
				_data.erase(entryIt);
			}
		}

	};

private:

	std::vector<std::unique_ptr<BucketType>> _buckets;
	Hash _hasher;

private:

	BucketType& getBucket(const Key& key) const
	{
		std::size_t bucketIndx = _hasher(key) % _buckets.size();
		return *_buckets[bucketIndx];
	}

public:

	typedef Key KeyType;
	typedef Value ValueType;
	typedef Hash HashType;

public:

	ParallelLookupTable(uint16_t numBuckets = 19)
		: _buckets(numBuckets)
	{
		for(uint16_t i = 0; i < numBuckets; ++i)
		{
			_buckets[i].reset(new BucketType());
		}
	}
	ParallelLookupTable(const ParallelLookupTable& table) = delete;
	ParallelLookupTable& operator=(const ParallelLookupTable& table) = delete;

	Value getValue(const Key& key, const Value& defaultValue)
	{
		return getBucket(key).getValue(key, defaultValue);
	}

	void addOrUpdate(const Key& key, const Value& value)
	{
		getBucket(key).addOrUpdate(key, value);
	}

	void remove(const Key& key)
	{
		getBucket(key).remove(key);
	}

	std::map<Key, Value> getMap()
	{
		std::map<Key, Value> res;

		for(auto& bucket : _buckets)
		{
			std::unique_lock lock(bucket->_dataLock);

			for(const auto& pair : bucket->_data)
			{
				res.insert(pair);
			}
		}

		return res;
	}

};