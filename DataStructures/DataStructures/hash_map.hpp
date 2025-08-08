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
	HashMap<TKey, TValue>::HashMap(HashMap&& rhs) noexcept
		: buckets_(std::move(rhs.buckets_)), hash_function_(std::move(rhs.hash_function_)), count_(rhs.count_)
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
		if (buckets_.Size() >= minBuckets && !trim)
			return;

		Array<LinkedList<KVPair>> newBuckets(minBuckets);

		for (auto& bucket : buckets_)
		{
			for (auto& pair : bucket)
			{
				size_t newIndex = hash_function_(pair.First()) % minBuckets;
				newBuckets[newIndex].PushBack(move(pair));
			}
		}

		buckets_ = move(newBuckets);
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::TrimExcess()
	{
		size_t newSize = count_ > 0 ? count_ : 1;
		EnsureCapacity(newSize, true);
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::TryAdd(const TKey& key, const TValue& value)
	{
		if (ContainsKey(key))
			return false;

		if (count_ >= buckets_.Size())
			EnsureCapacity(buckets_.Size() * 2 + 1);

		size_t index = BucketIndex(key);
		buckets_[index].PushBack(KVPair(key, value));
		++count_;
		return true;
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::Put(const TKey& key, const TValue& value)
	{
		KVPair* pair = FindPair(key);
		if (pair)
		{
			pair->Second(value);
		}
		else
		{
			if (count_ >= buckets_.Size())
				EnsureCapacity(buckets_.Size() * 2 + 1);

			size_t index = BucketIndex(key);
			buckets_[index].PushBack(KVPair(key, value));
			++count_;
		}
	}

	template <class TKey, class TValue>
	TValue& HashMap<TKey, TValue>::operator[](const TKey& key)
	{
		KVPair* pair = FindPair(key);
		if (pair)
			return pair->Second();

		if (count_ >= buckets_.Size())
			EnsureCapacity(buckets_.Size() * 2 + 1);

		size_t index = BucketIndex(key);
		buckets_[index].PushBack(KVPair(key, TValue{}));
		++count_;
		return buckets_[index].Back().Second();
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::TryGetValue(const TKey& key, TValue& outVal) const
	{
		const KVPair* pair = FindPair(key);
		if (pair)
		{
			outVal = pair->Second();
			return true;
		}
		return false;
	}

	template <class TKey, class TValue>
	const TValue& HashMap<TKey, TValue>::operator[](const TKey& key) const
	{
		const KVPair* pair = FindPair(key);
		if (!pair)
			throw adt_exception("Key not found");
		return pair->Second();
	}

	template <class TKey, class TValue>
	bool HashMap<TKey, TValue>::Remove(const TKey& key, TValue* removed)
	{
		size_t index = BucketIndex(key);
		auto& list = buckets_[index];
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (it->First() == key)
			{
				if (removed)
					*removed = it->Second();
				list.Erase(it);
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
		return buckets_.Size();
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::begin()
	{
		return buckets_.begin();
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::end()
	{
		return buckets_.end();
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::begin() const
	{
		return buckets_.begin();
	}

	template <class TKey, class TValue>
	auto HashMap<TKey, TValue>::end() const
	{
		return buckets_.end();
	}

	template <class TKey, class TValue>
	Array<TKey> HashMap<TKey, TValue>::Keys() const
	{
		Array<TKey> keys(count_);
		for (const auto& bucket : buckets_)
		{
			for (const auto& pair : bucket)
				keys.PushBack(pair.First());
		}
		return keys;
	}

	template <class TKey, class TValue>
	Array<TValue> HashMap<TKey, TValue>::Values() const
	{
		Array<TValue> values(count_);
		for (const auto& bucket : buckets_)
		{
			for (const auto& pair : bucket)
				values.PushBack(pair.Second());
		}
		return values;
	}

	template <class TKey, class TValue>
	size_t HashMap<TKey, TValue>::BucketIndex(const TKey& key) const noexcept
	{
		if (buckets_.Size() == 0)
			return 0;
		return hash_function_(key) % buckets_.Size();
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
