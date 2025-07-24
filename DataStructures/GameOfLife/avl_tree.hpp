#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "avl_node.hpp"
#include <functional>

#include "bst_base.hpp"
#include "bst_iterator.hpp"

namespace data_structures
{
    template <class K, class V>
    class AvlTree final : public BinarySearchTreeBase<K, V, AvlTree<K, V>, AvlNode<K, V>>
    {
        using Node = AvlNode<K, V>;
        using Base = BinarySearchTreeBase<K, V, AvlTree, AvlNode<K, V>>;

    public:
        using iterator = BstIterator<K, V, false, AvlNode<K, V>>;
        using const_iterator = BstIterator<K, V, true, AvlNode<K, V>>;

        AvlTree() = default;
        ~AvlTree() override;

        AvlTree(const AvlTree& copy);
        AvlTree& operator=(const AvlTree& rhs);
        AvlTree(AvlTree&& copy) noexcept;
        AvlTree& operator=(AvlTree&& rhs) noexcept;

        // Indexer
        V& operator[](const K& key);

        // Curiously Recurring Template Pattern (CRTP) override points
        std::pair<V&, bool> InsertImpl(const K& key, const V& value);
        void RemoveImpl(const K& key);

        // Iterators - forward only
        iterator begin() noexcept;
        iterator end() noexcept;

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;

        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;


    private:
        // Recursive operations
        std::pair<V&, bool> Insert(Node*& node, const K& key, const V& value, bool& taller);
        Node* Remove(Node* node, const K& key, bool& shorter);

        // Rotations and balancing
        void LeftBalance(Node*& node, bool& taller);
        void RightBalance(Node*& node, bool& taller);
        void RemoveLeftBalance(Node*& node, bool& shorter);
        void RemoveRightBalance(Node*& node, bool& shorter);

        Node* RotateLeft(Node* node);
        Node* RotateRight(Node* node);
    };

	
}


#endif // AVL_TREE_HPP