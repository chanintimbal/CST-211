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

		// CRTP hooks to be implemented by derived types
		Derived* DerivedThis() noexcept;
		const Derived* DerivedThis() const noexcept;
	};
}
#endif // BINARY_SEARCH_TREE_BASE_HPP
