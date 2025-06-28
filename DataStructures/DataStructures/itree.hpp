#ifndef ITREE_HPP
#define ITREE_HPP
#include <functional>
#include "pair_node.hpp"

namespace data_structures
{
	template <class K, class V>
	class ITree
	{
	public:
		virtual ~ITree() = default;

		virtual std::pair<V&, bool> insert(const K& key, const V& value) = 0;

		virtual V& at(const K& key) = 0;
		virtual const V& at(const K& key) const = 0;

		virtual V* find(const K& key) = 0;
		virtual const V* find(const K& key) const = 0;

		virtual void erase(const K& key) = 0;

		virtual bool Empty() const noexcept = 0;
		virtual void Clear() noexcept = 0;
		virtual size_t Height() const noexcept = 0;
		virtual void InOrder() const noexcept = 0;
		virtual void PreOrder() const noexcept = 0;
		virtual void PostOrder() const noexcept = 0;
		virtual void BreadthFirst() const noexcept = 0;

		virtual void VisitFunction(const std::function<void(const PairNode<K, V>*)>& visit) noexcept = 0;
	};
}

#endif