#ifndef BINARY_SEARCH_TREE_BASE_HPP
#define BINARY_SEARCH_TREE_BASE_HPP

#include "itree.hpp"
#include "bst_node.hpp"
#include <functional>
#include <cstddef>

#include "adt_exception.hpp"
#include "list_queue.hpp"

namespace data_structures
{
	template <class K, class V, class Derived, class NodeT>
	class BinarySearchTreeBase : public ITree<K, V>
	{
	public:
		BinarySearchTreeBase() = default;
		~BinarySearchTreeBase() override = default;

		std::pair<V&, bool> insert(const K& key, const V& value) override;
		void erase(const K& key) override;

		V& at(const K& key) override;
		const V& at(const K& key) const override;

		V* find(const K& key) override;
		const V* find(const K& key) const override;

		bool Empty() const noexcept override;
		void Clear() noexcept override;
		size_t Height() const noexcept override;

		void InOrder() const noexcept override;
		void PreOrder() const noexcept override;
		void PostOrder() const noexcept override;
		void BreadthFirst() const noexcept override;

		void VisitFunction(const std::function<void(const PairNode<K, V>*)>& visit) noexcept override;

		bool operator==(const BinarySearchTreeBase& rhs) const noexcept;
		bool operator!=(const BinarySearchTreeBase& rhs) const noexcept;


	protected:
		NodeT* root_ = nullptr;
		std::function<void(const PairNode<K, V>*)> visit_ = nullptr;

		virtual void Visit(const NodeT* node) const noexcept;

		void InOrder(const NodeT* node) const noexcept;
		void PreOrder(const NodeT* node) const noexcept;
		void PostOrder(const NodeT* node) const noexcept;
		void BreadthFirst(const NodeT* node) const noexcept;

		void Copy(const NodeT* node);

		static NodeT* MinNode(NodeT* node) noexcept;
		static const NodeT* MinNode(const NodeT* node) noexcept;

		void Clear(NodeT* node) noexcept;
		size_t Height(NodeT* node) const noexcept;

		bool Equals(NodeT* nodeA, NodeT* nodeB) const noexcept;

		static NodeT* FindNode(NodeT* node, const K& key) noexcept;
		static V* PtrTo(NodeT* node);

		NodeT*& Root() noexcept;
		const NodeT* Root() const noexcept;

		Derived* DerivedThis() noexcept;
		const Derived* DerivedThis() const noexcept;
	};

	template <class K, class V, class Derived, class NodeT>
	std::pair<V&, bool> BinarySearchTreeBase<K, V, Derived, NodeT>::insert(const K& key, const V& value)
	{
		return DerivedThis()->InsertImpl(key, value);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::erase(const K& key)
	{
		DerivedThis()->RemoveImpl(key);
	}

	template <class K, class V, class Derived, class NodeT>
	V& BinarySearchTreeBase<K, V, Derived, NodeT>::at(const K& key)
	{
		NodeT* node = FindNode(root_, key);
		if (!node)
			throw AdtException("Key not found");
		return node->Value();
	}

	template <class K, class V, class Derived, class NodeT>
	const V& BinarySearchTreeBase<K, V, Derived, NodeT>::at(const K& key) const
	{
		const NodeT* node = FindNode(root_, key);
		if (!node)
			throw AdtException("Key not found");
		return node->Value();
	}

	template <class K, class V, class Derived, class NodeT>
	V* BinarySearchTreeBase<K, V, Derived, NodeT>::find(const K& key)
	{
		NodeT* node = FindNode(root_, key);
		return PtrTo(node);
	}

	template <class K, class V, class Derived, class NodeT>
	const V* BinarySearchTreeBase<K, V, Derived, NodeT>::find(const K& key) const
	{
		const NodeT* node = FindNode(root_, key);
		return PtrTo(const_cast<NodeT*>(node));
	}

	template <class K, class V, class Derived, class NodeT>
	bool BinarySearchTreeBase<K, V, Derived, NodeT>::Empty() const noexcept
	{
		return root_ == nullptr;
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::Clear() noexcept
	{
		Clear(root_);
		root_ = nullptr;
	}

	template <class K, class V, class Derived, class NodeT>
	size_t BinarySearchTreeBase<K, V, Derived, NodeT>::Height() const noexcept
	{
		return Height(root_);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::InOrder() const noexcept
	{
		InOrder(root_);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::PreOrder() const noexcept
	{
		PreOrder(root_);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::PostOrder() const noexcept
	{
		PostOrder(root_);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::BreadthFirst() const noexcept
	{
		BreadthFirst(root_);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::VisitFunction(
		const std::function<void(const PairNode<K, V>*)>& visit) noexcept
	{
		visit_ = visit;
	}

	template <class K, class V, class Derived, class NodeT>
	bool BinarySearchTreeBase<K, V, Derived, NodeT>::operator==(const BinarySearchTreeBase& rhs) const noexcept
	{
		return Equals(root_, rhs.root_);
	}

	template <class K, class V, class Derived, class NodeT>
	bool BinarySearchTreeBase<K, V, Derived, NodeT>::operator!=(const BinarySearchTreeBase& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::Visit(const NodeT* node) const noexcept
	{
		if (node && visit_)
			visit_(node);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::InOrder(const NodeT* node) const noexcept
	{
		if (!node) return;
		InOrder(node->Left());
		Visit(node);
		InOrder(node->Right());
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::PreOrder(const NodeT* node) const noexcept
	{
		if (!node) return;
		Visit(node);
		PreOrder(node->Left());
		PreOrder(node->Right());
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::PostOrder(const NodeT* node) const noexcept
	{
		if (!node) return;
		PostOrder(node->Left());
		PostOrder(node->Right());
		Visit(node);
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::BreadthFirst(const NodeT* node) const noexcept
	{
		if (!node) return;
		ListQueue<const NodeT*> queue;
		queue.Enqueue(node);

		while (!queue.IsEmpty())
		{
			const NodeT* current = queue.Dequeue();
			Visit(current);
			if (current->Left())
				queue.Enqueue(current->Left());
			if (current->Right())
				queue.Enqueue(current->Right());
		}
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::Copy(const NodeT* node)
	{
		if (!node) return;
		DerivedThis()->InsertImpl(node->Key(), node->Value());
		Copy(node->Left());
		Copy(node->Right());
	}

	template <class K, class V, class Derived, class NodeT>
	NodeT* BinarySearchTreeBase<K, V, Derived, NodeT>::MinNode(NodeT* node) noexcept
	{
		if (!node) return nullptr;
		while (node->Left())
			node = node->Left();
		return node;
	}

	template <class K, class V, class Derived, class NodeT>
	const NodeT* BinarySearchTreeBase<K, V, Derived, NodeT>::MinNode(const NodeT* node) noexcept
	{
		if (!node) return nullptr;
		while (node->Left())
			node = node->Left();
		return node;
	}

	template <class K, class V, class Derived, class NodeT>
	void BinarySearchTreeBase<K, V, Derived, NodeT>::Clear(NodeT* node) noexcept
	{
		if (!node) return;
		Clear(node->Left());
		Clear(node->Right());
		delete node;
	}

	template <class K, class V, class Derived, class NodeT>
	size_t BinarySearchTreeBase<K, V, Derived, NodeT>::Height(NodeT* node) const noexcept
	{
		if (!node) return 0;
		size_t left_height = Height(node->Left());
		size_t right_height = Height(node->Right());
		return 1 + (left_height > right_height ? left_height : right_height);
	}

	template <class K, class V, class Derived, class NodeT>
	bool BinarySearchTreeBase<K, V, Derived, NodeT>::Equals(NodeT* nodeA, NodeT* nodeB) const noexcept
	{
		if (!nodeA && !nodeB) return true;
		if (!nodeA || !nodeB) return false;
		if (nodeA->Key() != nodeB->Key() || nodeA->Value() != nodeB->Value())
			return false;
		return Equals(nodeA->Left(), nodeB->Left()) && Equals(nodeA->Right(), nodeB->Right());
	}

	template <class K, class V, class Derived, class NodeT>
	NodeT* BinarySearchTreeBase<K, V, Derived, NodeT>::FindNode(NodeT* node, const K& key) noexcept
	{
		while (node)
		{
			if (key < node->Key())
				node = node->Left();
			else if (key > node->Key())
				node = node->Right();
			else
				return node;
		}
		return nullptr;
	}

	template <class K, class V, class Derived, class NodeT>
	V* BinarySearchTreeBase<K, V, Derived, NodeT>::PtrTo(NodeT* node)
	{
		if (!node) return nullptr;
		return &node->Value();
	}

	template <class K, class V, class Derived, class NodeT>
	NodeT*& BinarySearchTreeBase<K, V, Derived, NodeT>::Root() noexcept
	{
		return root_;
	}

	template <class K, class V, class Derived, class NodeT>
	const NodeT* BinarySearchTreeBase<K, V, Derived, NodeT>::Root() const noexcept
	{
		return root_;
	}

	template <class K, class V, class Derived, class NodeT>
	Derived* BinarySearchTreeBase<K, V, Derived, NodeT>::DerivedThis() noexcept
	{
		return static_cast<Derived*>(this);
	}

	template <class K, class V, class Derived, class NodeT>
	const Derived* BinarySearchTreeBase<K, V, Derived, NodeT>::DerivedThis() const noexcept
	{
		return static_cast<const Derived*>(this);
	}
}

#endif // BINARY_SEARCH_TREE_BASE_HPP
