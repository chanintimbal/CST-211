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
}
#endif // AVL_NODE_HPP