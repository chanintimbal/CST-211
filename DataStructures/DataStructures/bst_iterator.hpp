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
		explicit BstIterator(NodeT* n);
		explicit BstIterator(const NodeT* n);

		operator BstIterator<Key, Value, true, NodeT>() const;

		reference operator*() override;
		reference operator*() const override;
		pointer operator->() override;
		pointer operator->() const override;

		Base& operator++() override;
		Base& operator--() override;

		bool operator==(const Base& rhs) const override;
		bool operator!=(const Base& rhs) const override;

	private:
		NodeT* node_ {nullptr};

		static NodeT* Min(NodeT* node) noexcept;
		static NodeT* Max(NodeT* node) noexcept;
		static NodeT* Next(NodeT* node) noexcept;
		static NodeT* Prev(NodeT* node) noexcept;
	};
}
#endif
