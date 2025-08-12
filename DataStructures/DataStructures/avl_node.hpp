#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

#include "pair_node.hpp"
#include <cstdint>

namespace data_structures
{
	enum class AvlNodeBalanceFactor : int8_t
	{
		LeftHeavy = -1,
		Equal = 0,
		RightHeavy = 1
	};

	template <class K, class V>
	class AvlNode final : public PairNode<K, V>
	{
	public:
		AvlNode(const K& key, const V& value, AvlNode* left = nullptr, AvlNode* right = nullptr);
		virtual ~AvlNode() override = default;

		AvlNode(const AvlNode& copy);
		AvlNode& operator=(const AvlNode& rhs);

		AvlNode(AvlNode&& copy) noexcept;
		AvlNode& operator=(AvlNode&& rhs) noexcept;

		// Accessors
		AvlNode*& Left() noexcept;
		AvlNode*& Right() noexcept;

		AvlNode* Left() const noexcept;
		AvlNode* Right() const noexcept;

		void Left(AvlNode* left) noexcept;
		void Right(AvlNode* right) noexcept;

		AvlNodeBalanceFactor BalanceFactor() const noexcept;
		void BalanceFactor(AvlNodeBalanceFactor bf) noexcept;

		AvlNode* Parent() const noexcept;
		AvlNode*& Parent() noexcept;
		void Parent(AvlNode* p) noexcept;

		using IsBinarySearchTreeNode = void; // marker type
		using KeyType = K;
		using ValueType = V;

	private:
		AvlNode* left_{ nullptr };
		AvlNode* right_{ nullptr };
		AvlNode* parent_{ nullptr };
		AvlNodeBalanceFactor balance_factor_{ AvlNodeBalanceFactor::Equal };
	};

	template <class K, class V>
	AvlNode<K, V>::AvlNode(const K& key, const V& value, AvlNode* left, AvlNode* right)
		: PairNode<K, V>(key, value), left_(left), right_(right)
	{	}

	template <class K, class V>
	AvlNode<K, V>::AvlNode(const AvlNode& copy)
		: PairNode<K, V>(copy), left_(copy.left), right_(copy.right), parent_(copy.parent), balance_factor_(copy.balance_factor_)
	{	}

	template <class K, class V>
	AvlNode<K, V>& AvlNode<K, V>::operator=(const AvlNode& rhs)
	{
		if (this != &rhs)
		{
			PairNode<K, V>::operator=(rhs);
			left_ = rhs.left;
			right_ = rhs.right;
			parent_ = rhs.parent_;
			balance_factor_ = rhs.balance_factor_;
		}
		return *this;
	}

	template <class K, class V>
	AvlNode<K, V>::AvlNode(AvlNode&& copy) noexcept
		: PairNode<K,V>(std::move(copy)), left_(copy.left_), right_(copy.right_), parent_(copy.parent), balance_factor_(copy.balance_factor_)
	{
		copy.left_ = nullptr;
		copy.right_ = nullptr;
		copy.parent_ = nullptr;
		copy.balance_factor_ = AvlNodeBalanceFactor::Equal;
	}

	template <class K, class V>
	AvlNode<K, V>& AvlNode<K, V>::operator=(AvlNode&& rhs) noexcept
	{
		if (this != &rhs)
		{
			PairNode<K, V>::operator=(std::move(rhs));
			left_ = rhs.left;
			right_ = rhs.right;
			parent_ = rhs.parent;
			balance_factor_ = rhs.balance_factor_;

			rhs.left_ = nullptr;
			rhs.right_ = nullptr;
			rhs.parent_ = nullptr;
			rhs.balance_factor_ = AvlNodeBalanceFactor::Equal;
		}
		return *this;
	}

	template <class K, class V>
	AvlNode<K, V>*& AvlNode<K, V>::Left() noexcept
	{
		return left_;
	}

	template <class K, class V>
	AvlNode<K, V>*& AvlNode<K, V>::Right() noexcept
	{
		return right_;
	}

	template <class K, class V>
	AvlNode<K, V>* AvlNode<K, V>::Left() const noexcept
	{
		return left_;
	}

	template <class K, class V>
	AvlNode<K, V>* AvlNode<K, V>::Right() const noexcept
	{
		return right_;
	}

	template <class K, class V>
	void AvlNode<K, V>::Left(AvlNode* left) noexcept
	{
		left_ = left;
		if (left_)
			left_->Parent(this);
	}

	template <class K, class V>
	void AvlNode<K, V>::Right(AvlNode* right) noexcept
	{
		right_ = right;
		if (right_)
			right_->Parent(this);
	}


	template <class K, class V>
	AvlNodeBalanceFactor AvlNode<K, V>::BalanceFactor() const noexcept
	{
		return balance_factor_;
	}

	template <class K, class V>
	void AvlNode<K, V>::BalanceFactor(AvlNodeBalanceFactor bf) noexcept
	{
		balance_factor_ = bf;
	}

	template <class K, class V>
	AvlNode<K, V>* AvlNode<K, V>::Parent() const noexcept
	{
		return parent_;
	}

	template <class K, class V>
	AvlNode<K, V>*& AvlNode<K, V>::Parent() noexcept
	{
		return parent_;
	}

	template <class K, class V>
	void AvlNode<K, V>::Parent(AvlNode* p) noexcept
	{
		parent_ = p;
	}
}
#endif // AVL_NODE_HPP