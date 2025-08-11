#ifndef BST_NODE_HPP
#define BST_NODE_HPP

#include "pair_node.hpp"

namespace data_structures
{
	template <class K, class V>
	class BstNode final : public PairNode<K, V>
	{
	public:
		BstNode(const K& key, const V& value, BstNode* left = nullptr, BstNode* right = nullptr);

		virtual ~BstNode() override = default;

		BstNode(const BstNode& copy) noexcept = default;
		BstNode& operator=(const BstNode& rhs) noexcept = default;
		BstNode(BstNode&& copy) noexcept = default;
		BstNode& operator=(BstNode&& rhs) noexcept = default;

		BstNode*& Left() noexcept;
		BstNode*& Right() noexcept;
		BstNode*& Parent() noexcept;

		BstNode* const& Left() const noexcept;
		BstNode* const& Right() const noexcept;
		BstNode* const& Parent() const noexcept;

		void Left(BstNode* left) noexcept;
		void Right(BstNode* right) noexcept;
		void Parent(BstNode* parent) noexcept;

		using KeyType = K;
		using ValueType = V;

	private:
		BstNode* left_{ nullptr };
		BstNode* right_{ nullptr };
		BstNode* parent_{ nullptr };
	};

	template <class K, class V>
	BstNode<K, V>::BstNode(const K& key, const V& value, BstNode* left, BstNode* right)
		: PairNode<K, V>(key, value), left_(left), right_(right)
	{
	}

	template <class K, class V>
	BstNode<K, V>*& BstNode<K, V>::Left() noexcept
	{
		return left_;
	}

	template <class K, class V>
	BstNode<K, V>*& BstNode<K, V>::Right() noexcept
	{
		return right_;
	}

	template <class K, class V>
	BstNode<K, V>*& BstNode<K, V>::Parent() noexcept
	{
		return parent_;
	}

	template <class K, class V>
	BstNode<K, V>* const& BstNode<K, V>::Left() const noexcept
	{
		return left_;
	}

	template <class K, class V>
	BstNode<K, V>* const& BstNode<K, V>::Right() const noexcept
	{
		return right_;
	}

	template <class K, class V>
	BstNode<K, V>* const& BstNode<K, V>::Parent() const noexcept
	{
		return parent_;
	}

	template <class K, class V>
	void BstNode<K, V>::Left(BstNode* left) noexcept
	{
		left_ = left;
	}

	template <class K, class V>
	void BstNode<K, V>::Right(BstNode* right) noexcept
	{
		right_ = right;
	}

	template <class K, class V>
	void BstNode<K, V>::Parent(BstNode* parent) noexcept
	{
		parent_ = parent;
	}
}
#endif
