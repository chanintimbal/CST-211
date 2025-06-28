#ifndef BST_TREE_HPP
#define BST_TREE_HPP

#include "bst_base.hpp"
#include "bst_node.hpp"
#include "bst_iterator.hpp"
#include "list_queue.hpp"
#include <functional>
#include <utility>

namespace data_structures
{
	template <class K, class V>
	class BstTree final : public BinarySearchTreeBase<K, V, BstTree<K, V>, BstNode<K, V>>
	{
		using Node = BstNode<K, V>;
		using Base = BinarySearchTreeBase<K, V, BstTree, BstNode<K, V>>;

	public:
		using iterator = BstIterator<K, V, false>;
		using const_iterator = BstIterator<K, V, true>;

		BstTree() = default;
		~BstTree() override;

		BstTree(const BstTree& copy);
		BstTree& operator=(const BstTree& rhs);
		BstTree(BstTree&& copy) noexcept;
		BstTree& operator=(BstTree&& rhs) noexcept;

		std::pair<V&, bool> InsertImpl(const K& key, const V& value);
		void RemoveImpl(const K& key);

		// Indexer
		V& operator[](const K& key);

		// Iterators - forward only
		iterator begin() noexcept;
		iterator end() noexcept;

		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;

		const_iterator cbegin() const noexcept;
		static const_iterator cend() noexcept;

	private:
		std::pair<V&, bool> Insert(Node*& cur, const K& key, const V& value, Node* parent);
		void Remove(Node*& cur, const K& key);

		V& Lookup(Node* cur, const K& key) const;
		V* LookupPtr(Node* cur, const K& key) const;
	};	
}
#endif
