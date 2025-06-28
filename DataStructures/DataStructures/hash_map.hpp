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

		HashMap(const HashMap& rhs);              // deep copy
		HashMap& operator=(const HashMap& rhs);   // copy-assign
		HashMap(HashMap&& rhs) noexcept;          // move
		HashMap& operator=(HashMap&& rhs) noexcept;
		~HashMap() = default;

		// capacity helpers
		void EnsureCapacity(size_t minBuckets, bool trim = false);
		void TrimExcess();

		// insertion / update
		bool TryAdd(const TKey& key, const TValue& value); // false if key exists
		void Put(const TKey& key, const TValue& value);    // add or overwrite

		TValue& operator[](const TKey& key);               // add default if absent

		// retrieval
		bool TryGetValue(const TKey& key, TValue& outVal) const;
		const TValue& operator[](const TKey& key) const;   // throws if missing

		// removal
		bool Remove(const TKey& key, TValue* removed = nullptr);

		// queries
		bool ContainsKey(const TKey& key) const;
		bool ContainsValue(const TValue& v) const;
		size_t Count() const noexcept;

		// misc
		void Clear();
		size_t TableSize() const noexcept;

		// iteration
		auto begin();
		auto end();
		auto begin() const;
		auto end() const;

		// views
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


}
#endif