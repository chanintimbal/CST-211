#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <functional>
#include <utility>
#include "adt_exception.hpp"
#include "linked_list.hpp"
#include "array.hpp"
#include "pair.hpp"

using std::function;
using std::move;

namespace data_structures
{
	template <class TKey, class TValue>
	class HashMap final
	{
	public:

		using KVPair = data_structures::Pair<TKey, TValue>;

		explicit HashMap(size_t tableSize, const function<size_t(const TKey&)>& hashFn);

		HashMap(const HashMap& rhs);
		HashMap& operator=(const HashMap& rhs);
		HashMap(HashMap&& rhs) noexcept;
		HashMap& operator=(HashMap&& rhs) noexcept;
		~HashMap() = default;

		void EnsureCapacity(size_t minBuckets, bool trim = false);
		void TrimExcess();

		bool TryAdd(const TKey& key, const TValue& value);
		void Put(const TKey& key, const TValue& value);

		TValue& operator[](const TKey& key);

		bool TryGetValue(const TKey& key, TValue& outVal) const;
		const TValue& operator[](const TKey& key) const;

		bool Remove(const TKey& key, TValue* removed = nullptr);

		bool ContainsKey(const TKey& key) const;
		bool ContainsValue(const TValue& v) const;
		size_t Count() const noexcept;

		void Clear();
		size_t TableSize() const noexcept;

		auto begin();
		auto end();
		auto begin() const;
		auto end() const;

		Array<TKey> Keys() const;
		Array<TValue> Values() const;

	private:
		Array<LinkedList<KVPair>> buckets_;
		function<size_t(const TKey&)> hash_function_{};
		size_t count_{ 0 };

		size_t BucketIndex(const TKey& key) const noexcept;
		KVPair* FindPair(const TKey& key);
		const KVPair* FindPair(const TKey& key) const;
	};


	template <class TKey, class TValue>
	HashMap<TKey, TValue>::HashMap(size_t tableSize, const function<size_t(const TKey&)>& hashFn)
		: buckets_(tableSize), hash_function_(hashFn)
	{
	}

	template <class TKey, class TValue>
	HashMap<TKey, TValue>::HashMap(const HashMap& rhs)
		: buckets_(rhs.buckets_), hash_function_(rhs.hash_function_), count_(rhs.count_)
	{
	}

	template <class TKey, class TValue>
	HashMap<TKey, TValue>& HashMap<TKey, TValue>::operator=(const HashMap& rhs)
	{
		if (this != &rhs)
		{
			HashMap temp(rhs);
			std::swap(buckets_, temp.buckets_);
			std::swap(hash_function_, temp.hash_function_);
			std::swap(count_, temp.count_);
		}
		return *this;
	}

	template <class TKey, class TValue>
	HashMap<TKey, TValue>::HashMap(HashMap&& rhs) noexcept : buckets_(std::move(rhs.buckets_)), hash_function_(std::move(rhs.hash_function_)), count_(rhs.count_)
	{
		rhs.count_ = 0;
	}

	template <class TKey, class TValue>
	HashMap<TKey, TValue>& HashMap<TKey, TValue>::operator=(HashMap&& rhs) noexcept
	{
		if (this != &rhs)
		{
			buckets_ = std::move(rhs.buckets_);
			hash_function_ = std::move(rhs.hash_function_);
			count_ = rhs.count_;
			rhs.count_ = 0;
		}
		return *this;
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::EnsureCapacity(size_t minBuckets, bool trim)
	{
		if (minBuckets <= buckets_.size() && !trim)
			return;

		size_t newSize = minBuckets > buckets_.size() ? minBuckets : buckets_.size();
		Array<LinkedList<KVPair>> newBuckets(newSize);

		for (auto& bucket : buckets_)
		{
			for (auto& pair : bucket)
			{
				size_t newIndex = hash_function_(pair.First()) % newSize;
				newBuckets[newIndex].Append(pair);
			}
		}

		buckets_ = std::move(newBuckets);
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::TrimExcess()
	{
		EnsureCapacity(count_, true);
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::TryAdd(const TKey& key, const TValue& value)
	{
		if (ContainsKey(key))
			return false;

		if (count_ >= buckets_.size())
			EnsureCapacity(buckets_.size() * 2 + 1);

		size_t index = BucketIndex(key);
		buckets_[index].Append(KVPair(key, value));
		++count_;
		return true;
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::Put(const TKey& key, const TValue& value)
	{
		if (count_ >= buckets_.size())
			EnsureCapacity(buckets_.size() * 2 + 1);

		size_t index = BucketIndex(key);
		for (auto& pair : buckets_[index])
		{
			if (pair.First() == key)
			{
				pair.Second(value);
				return;
			}
		}

		buckets_[index].Append(KVPair(key, value));
		++count_;
	}

	template <class TKey, class TValue>
	TValue& HashMap<TKey, TValue>::operator[](const TKey& key)
	{
		size_t index = BucketIndex(key);
		for (auto& pair : buckets_[index])
		{
			if (pair.First() == key)
				return pair.Second();
		}

		if (count_ >= buckets_.size())
			EnsureCapacity(buckets_.size() * 2 + 1);

		index = BucketIndex(key);
		buckets_[index].Append(KVPair(key, TValue{}));
		++count_;
		return buckets_[index].Last().Second();
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::TryGetValue(const TKey& key, TValue& outVal) const
	{
		const KVPair* pair = FindPair(key);
		if (!pair)
			return false;

		outVal = pair->Second();
		return true;
	}

	template <class TKey, class TValue>
	const TValue& HashMap<TKey, TValue>::operator[](const TKey& key) const
	{
		const KVPair* pair = FindPair(key);
		if (!pair)
			throw AdtException("Key not found");
		return pair->Second();
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::Remove(const TKey& key, TValue* removed)
	{
		size_t index = BucketIndex(key);
		auto& bucket = buckets_[index];

		for (auto it = bucket.begin(); it != bucket.end(); ++it)
		{
			if (it->First() == key)
			{
				if (removed)
					*removed = it->Second();
				bucket.Remove(*it);
				--count_;
				return true;
			}
		}

		return false;
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::ContainsKey(const TKey& key) const
	{
		return FindPair(key) != nullptr;
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::ContainsValue(const TValue& v) const
	{
		for (const auto& bucket : buckets_)
		{
			for (const auto& pair : bucket)
			{
				if (pair.Second() == v)
					return true;
			}
		}
		return false;
	}

	template <class TKey, class TValue>
	size_t HashMap<TKey, TValue>::Count() const noexcept
	{
		return count_;
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::Clear()
	{
		for (auto& bucket : buckets_)
			bucket.Clear();

		count_ = 0;
	}

	template <class TKey, class TValue>
	size_t HashMap<TKey, TValue>::TableSize() const noexcept
	{
		return buckets_.size();
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::begin()
	{
		// Could be implemented for iteration over all elements if desired
		throw AdtException("Not implemented");
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::end()
	{
		throw AdtException("Not implemented");
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::begin() const
	{
		throw AdtException("Not implemented");
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::end() const
	{
		throw AdtException("Not implemented");
	}

	template <class TKey, class TValue>
	Array<TKey> HashMap<TKey, TValue>::Keys() const
	{
		Array<TKey> keys(count_);
		size_t i = 0;
		for (const auto& bucket : buckets_)
		{
			for (const auto& pair : bucket)
			{
				keys[i++] = pair.First();
			}
		}
		return keys;
	}

	template <class TKey, class TValue>
	Array<TValue> HashMap<TKey, TValue>::Values() const
	{
		Array<TValue> values(count_);
		size_t i = 0;
		for (const auto& bucket : buckets_)
		{
			for (const auto& pair : bucket)
			{
				values[i++] = pair.Second();
			}
		}
		return values;
	}

	template <class TKey, class TValue>
	size_t HashMap<TKey, TValue>::BucketIndex(const TKey& key) const noexcept
	{
		return hash_function_(key) % buckets_.size();
	}

	template <class TKey, class TValue>
	typename HashMap<TKey, TValue>::KVPair* HashMap<TKey, TValue>::FindPair(const TKey& key)
	{
		size_t index = BucketIndex(key);
		for (auto& pair : buckets_[index])
		{
			if (pair.First() == key)
				return &pair;
		}
		return nullptr;
	}

	template <class TKey, class TValue>
	const typename HashMap<TKey, TValue>::KVPair* HashMap<TKey, TValue>::FindPair(const TKey& key) const
	{
		size_t index = BucketIndex(key);
		for (const auto& pair : buckets_[index])
		{
			if (pair.First() == key)
				return &pair;
		}
		return nullptr;
	}
}

#endif
