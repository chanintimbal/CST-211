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


    template <class K, class V>
    AvlTree<K, V>::~AvlTree()
    {
        this->Clear();
    }

    template <class K, class V>
    AvlTree<K, V>::AvlTree(const AvlTree& copy)
    {
        this->Copy(copy.Root());
    }

    template <class K, class V>
    AvlTree<K, V>& AvlTree<K, V>::operator=(const AvlTree& rhs)
    {
        if (this != &rhs)
        {
            this->Clear();
            this->Copy();
        }
        return *this;
    }

    template <class K, class V>
    AvlTree<K, V>::AvlTree(AvlTree&& copy) noexcept
    {
        this->Root() = copy.Root();
        copy.Root() = nullptr;
    }

    template <class K, class V>
    AvlTree<K, V>& AvlTree<K, V>::operator=(AvlTree&& rhs) noexcept
    {
        if (this != &rhs)
        {
            this->Clear();
            this->Root() = rhs.Root();
            rhs.Root() = nullptr;
        }
        return *this;
    }

    template <class K, class V>
    V& AvlTree<K, V>::operator[](const K& key)
    {
        return Base::insert(key, V{}).first;
    }

    template <class K, class V>
    std::pair<V&, bool> AvlTree<K, V>::InsertImpl(const K& key, const V& value)
    {
        bool taller = false;
        return Insesrt(this->Root(), key, value, taller);
    }

    template <class K, class V>
    void AvlTree<K, V>::RemoveImpl(const K& key)
    {
        bool shorter = false;
        this->Root() = Remove(this->Root(), key, shorter);
    }

    template <class K, class V>
    typename AvlTree<K, V>::iterator AvlTree<K, V>::begin() noexcept
    {
        return iterator(this->MinNode(this->Root()));
    }

    template <class K, class V>
    typename AvlTree<K, V>::iterator AvlTree<K, V>::end() noexcept
    {
        return iterator(static_cast<Node*>(nullptr));
    }

    template <class K, class V>
    typename AvlTree<K, V>::const_iterator AvlTree<K, V>::begin() const noexcept
    {
        return cbegin();
    }

    template <class K, class V>
    typename AvlTree<K, V>::const_iterator AvlTree<K, V>::end() const noexcept
    {
        return cend();
    }

    template <class K, class V>
    typename AvlTree<K, V>::const_iterator AvlTree<K, V>::cbegin() const noexcept
    {
        return iterator(this->MinNode(this->Root()));
    }

    template <class K, class V>
    typename AvlTree<K, V>::const_iterator AvlTree<K, V>::cend() const noexcept
    {
        return iterator(static_cast<Node*>(nullptr));
    }

    template <class K, class V>
    std::pair<V&, bool> AvlTree<K, V>::Insert(Node*& node, const K& key, const V& value, bool& taller)
    {
        return { V{}, false };
    }

    template <class K, class V>
    typename AvlTree<K, V>::Node* AvlTree<K, V>::Remove(Node* node, const K& key, bool& shorter)
    {
        return nullptr;
    }

    template <class K, class V>
    void AvlTree<K, V>::LeftBalance(Node*& node, bool& taller)
    {
    }

    template <class K, class V>
    void AvlTree<K, V>::RightBalance(Node*& node, bool& taller)
    {
    }

    template <class K, class V>
    void AvlTree<K, V>::RemoveLeftBalance(Node*& node, bool& shorter)
    {
    }

    template <class K, class V>
    void AvlTree<K, V>::RemoveRightBalance(Node*& node, bool& shorter)
    {
    }

    template <class K, class V>
    typename AvlTree<K, V>::Node* AvlTree<K, V>::RotateLeft(Node* node)
    {
        Node* right = node->Right();
        node->Right(right->Left());
        if (right->Left())
            right->Left()->Parent(node); //Sets parent
        right->Left(node);

        right->Parent(node->Parent()); //new subtree root takes original parent
        node->Parent(right);

        return right;
    }

    template <class K, class V>
    typename AvlTree<K, V>::Node* AvlTree<K, V>::RotateRight(Node* node)
    {
        Node* left = node->Left();
        node->Left(left->RIght());

        if (left->Right())
            left->Right()->Parent(node);
        left->Right(node);

        left->Parent(node->Parent());
        node->Parent(left);

        return left;
    }
}


#endif // AVL_TREE_HPP