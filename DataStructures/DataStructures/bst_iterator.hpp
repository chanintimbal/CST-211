#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

#include "adt_exception.hpp"
#include "i_adt_iterator.hpp"
#include "pair_node.hpp"
#include "bst_node.hpp"

namespace data_structures
{
	template<class Key, class Value, bool IsConst, class NodeT = BstNode<Key, Value>>
	class BstIterator : public IAdtIterator<std::conditional_t<IsConst, const PairNode<Key, Value>, PairNode<Key, Value>>>
	{
		using Base = IAdtIterator<std::conditional_t<IsConst, const PairNode<Key, Value>, PairNode<Key, Value>>>;

	public:
		using typename Base::iterator_category;
		using typename Base::value_type;
		using typename Base::reference;
		using typename Base::pointer;

		BstIterator() = default;
		explicit BstIterator(NodeT* n) : node_(n) {}
		explicit BstIterator(const NodeT* n) : node_(const_cast<NodeT*>(n)) {}

		operator BstIterator<Key, Value, true, NodeT>() const
		{
			return BstIterator<Key, Value, true, NodeT>(node_);
		}

		reference operator*() override
		{
			if (!node_) throw AdtException("Dereferencing null BST iterator");
			return *node_;
		}

		reference operator*() const override
		{
			if (!node_) throw AdtException("Dereferencing null BST iterator");
			return *node_;
		}

		pointer operator->() override
		{
			if (!node_) throw AdtException("Dereferencing null BST iterator");
			return node_;
		}

		pointer operator->() const override
		{
			if (!node_) throw AdtException("Dereferencing null BST iterator");
			return node_;
		}

		Base& operator++() override
		{
			node_ = Next(node_);
			return *this;
		}

		Base& operator--() override
		{
			node_ = Prev(node_);
			return *this;
		}

		bool operator==(const Base& rhs) const override
		{
			auto other = dynamic_cast<const BstIterator*>(&rhs);
			return other && node_ == other->node_;
		}

		bool operator!=(const Base& rhs) const override
		{
			return !(*this == rhs);
		}

	private:
		NodeT* node_{ nullptr };

		static NodeT* Min(NodeT* node) noexcept
		{
			if (!node) return nullptr;
			while (node->Left()) node = node->Left();
			return node;
		}

		static NodeT* Max(NodeT* node) noexcept
		{
			if (!node) return nullptr;
			while (node->Right()) node = node->Right();
			return node;
		}

		static NodeT* Next(NodeT* node) noexcept
		{
			if (!node) return nullptr;
			if (node->Right())
				return Min(node->Right());

			NodeT* parent = node->Parent();
			while (parent && node == parent->Right())
			{
				node = parent;
				parent = parent->Parent();
			}
			return parent;
		}

		static NodeT* Prev(NodeT* node) noexcept
		{
			if (!node) return nullptr;
			if (node->Left())
				return Max(node->Left());

			NodeT* parent = node->Parent();
			while (parent && node == parent->Left())
			{
				node = parent;
				parent = parent->Parent();
			}
			return parent;
		}
	};
}
#endif
