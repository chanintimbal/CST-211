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

        V& operator[](const K& key);

        std::pair<V&, bool> InsertImpl(const K& key, const V& value);
    	void RemoveImpl(const K& key);

        iterator begin() noexcept;
        iterator end() noexcept;

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;

        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

    private:
        std::pair<V&, bool> Insert(Node*& node, const K& key, const V& value, bool& taller);
        Node* Remove(Node* node, const K& key, bool& shorter);

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
            this->Copy(rhs.Root());
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
        return Insert(this->Root(), key, value, taller);
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
        if (!node)
        {
            node = new Node(key, value);
            node->BalanceFactor(AvlNodeBalanceFactor::Equal);
            taller = true;
            return { node->Value(), true };
        }

        if (key == node->Key())
        {
            taller = false;
            return { node->Value(), false };
        }

        if (key < node->Key())
        {
            auto result = Insert(node->Left(), key, value, taller);
            if (taller)
            {
                switch (node->BalanceFactor())
                {
                case AvlNodeBalanceFactor::LeftHeavy:
                    LeftBalance(node, taller);
                    break;
                case AvlNodeBalanceFactor::Equal:
                    node->BalanceFactor(AvlNodeBalanceFactor::LeftHeavy);
                    break;
                case AvlNodeBalanceFactor::RightHeavy:
                    node->BalanceFactor(AvlNodeBalanceFactor::Equal);
                    taller = false;
                    break;
                }
            }
            return result;
        }
        else
        {
            auto result = Insert(node->Right(), key, value, taller);
            if (taller)
            {
                switch (node->BalanceFactor())
                {
                case AvlNodeBalanceFactor::RightHeavy:
                    RightBalance(node, taller);
                    break;
                case AvlNodeBalanceFactor::Equal:
                    node->BalanceFactor(AvlNodeBalanceFactor::RightHeavy);
                    break;
                case AvlNodeBalanceFactor::LeftHeavy:
                    node->BalanceFactor(AvlNodeBalanceFactor::Equal);
                    taller = false;
                    break;
                }
            }
            return result;
        }
    }

    template <class K, class V>
    typename AvlTree<K, V>::Node* AvlTree<K, V>::Remove(Node* node, const K& key, bool& shorter)
    {
        if (!node)
        {
            shorter = false;
            return nullptr;
        }

        if (key == node->Key())
        {
            if (!node->Left() && !node->Right())
            {
                delete node;
                shorter = true;
                return nullptr;
            }
            else if (!node->Left())
            {
                Node* right = node->Right();
                right->Parent(node->Parent());
                delete node;
                shorter = true;
                return right;
            }
            else if (!node->Right())
            {
                Node* left = node->Left();
                left->Parent(node->Parent());
                delete node;
                shorter = true;
                return left;
            }
            else
            {
                Node* successor = node->Right();
                while (successor->Left())
                    successor = successor->Left();
                node->Key() = successor->Key();
                node->Value() = successor->Value();
                node->Right(Remove(node->Right(), successor->Key(), shorter));
                if (shorter)
                    RemoveRightBalance(node, shorter);
                return node;
            }
        }
        else if (key < node->Key())
        {
            node->Left(Remove(node->Left(), key, shorter));
            if (shorter)
                RemoveLeftBalance(node, shorter);
            return node;
        }
        else
        {
            node->Right(Remove(node->Right(), key, shorter));
            if (shorter)
                RemoveRightBalance(node, shorter);
            return node;
        }
    }

    template <class K, class V>
    void AvlTree<K, V>::LeftBalance(Node*& node, bool& taller)
    {
        Node* left = node->Left();
        switch (left->BalanceFactor())
        {
        case AvlNodeBalanceFactor::LeftHeavy:  // Single right rotation
            node = RotateRight(node);
            node->BalanceFactor(AvlNodeBalanceFactor::Equal);
            node->Right()->BalanceFactor(AvlNodeBalanceFactor::Equal);
            taller = false;
            break;

        case AvlNodeBalanceFactor::RightHeavy: // Double rotation: Left-Right
        {
            Node* leftRight = left->Right();
            switch (leftRight->BalanceFactor())
            {
            case AvlNodeBalanceFactor::LeftHeavy:
                node->BalanceFactor(AvlNodeBalanceFactor::RightHeavy);
                left->BalanceFactor(AvlNodeBalanceFactor::Equal);
                break;
            case AvlNodeBalanceFactor::Equal:
                node->BalanceFactor(AvlNodeBalanceFactor::Equal);
                left->BalanceFactor(AvlNodeBalanceFactor::Equal);
                break;
            case AvlNodeBalanceFactor::RightHeavy:
                node->BalanceFactor(AvlNodeBalanceFactor::Equal);
                left->BalanceFactor(AvlNodeBalanceFactor::LeftHeavy);
                break;
            }
            leftRight->BalanceFactor(AvlNodeBalanceFactor::Equal);

            node->Left(RotateLeft(left));
            node = RotateRight(node);
            taller = false;
            break;
        }
        case AvlNodeBalanceFactor::Equal:
            // This case shouldn't happen on insertion, but handle gracefully
            node->BalanceFactor(AvlNodeBalanceFactor::LeftHeavy);
            break;
        }
    }

    template <class K, class V>
    void AvlTree<K, V>::RightBalance(Node*& node, bool& taller)
    {
        Node* right = node->Right();
        switch (right->BalanceFactor())
        {
        case AvlNodeBalanceFactor::RightHeavy: // Single left rotation
            node = RotateLeft(node);
            node->BalanceFactor(AvlNodeBalanceFactor::Equal);
            node->Left()->BalanceFactor(AvlNodeBalanceFactor::Equal);
            taller = false;
            break;

        case AvlNodeBalanceFactor::LeftHeavy:  // Double rotation: Right-Left
        {
            Node* rightLeft = right->Left();
            switch (rightLeft->BalanceFactor())
            {
            case AvlNodeBalanceFactor::RightHeavy:
                node->BalanceFactor(AvlNodeBalanceFactor::LeftHeavy);
                right->BalanceFactor(AvlNodeBalanceFactor::Equal);
                break;
            case AvlNodeBalanceFactor::Equal:
                node->BalanceFactor(AvlNodeBalanceFactor::Equal);
                right->BalanceFactor(AvlNodeBalanceFactor::Equal);
                break;
            case AvlNodeBalanceFactor::LeftHeavy:
                node->BalanceFactor(AvlNodeBalanceFactor::Equal);
                right->BalanceFactor(AvlNodeBalanceFactor::RightHeavy);
                break;
            }
            rightLeft->BalanceFactor(AvlNodeBalanceFactor::Equal);

            node->Right(RotateRight(right));
            node = RotateLeft(node);
            taller = false;
            break;
        }
        case AvlNodeBalanceFactor::Equal:
            // This case shouldn't happen on insertion, but handle gracefully
            node->BalanceFactor(AvlNodeBalanceFactor::RightHeavy);
            break;
        }
    }


    template <class K, class V>
    void AvlTree<K, V>::RemoveLeftBalance(Node*& node, bool& shorter)
    {
        switch (node->BalanceFactor())
        {
        case AvlNodeBalanceFactor::LeftHeavy:
            node->BalanceFactor(AvlNodeBalanceFactor::Equal);
            break;
        case AvlNodeBalanceFactor::Equal:
            node->BalanceFactor(AvlNodeBalanceFactor::RightHeavy);
            shorter = false;
            break;
        case AvlNodeBalanceFactor::RightHeavy:
            RightBalance(node, shorter);
            break;
        }
    }

    template <class K, class V>
    void AvlTree<K, V>::RemoveRightBalance(Node*& node, bool& shorter)
    {
        switch (node->BalanceFactor())
        {
        case AvlNodeBalanceFactor::RightHeavy:
            node->BalanceFactor(AvlNodeBalanceFactor::Equal);
            break;
        case AvlNodeBalanceFactor::Equal:
            node->BalanceFactor(AvlNodeBalanceFactor::LeftHeavy);
            shorter = false;
            break;
        case AvlNodeBalanceFactor::LeftHeavy:
            LeftBalance(node, shorter);
            break;
        }
    }

    template <class K, class V>
    typename AvlTree<K, V>::Node* AvlTree<K, V>::RotateLeft(Node* node)
    {
        Node* right = node->Right();
        node->Right(right->Left());
        if (right->Left())
            right->Left()->Parent(node);
        right->Left(node);
        right->Parent(node->Parent());
        node->Parent(right);
        return right;
    }

    template <class K, class V>
    typename AvlTree<K, V>::Node* AvlTree<K, V>::RotateRight(Node* node)
    {
        Node* left = node->Left();
        node->Left(left->Right());
        if (left->Right())
            left->Right()->Parent(node);
        left->Right(node);
        left->Parent(node->Parent());
        node->Parent(left);
        return left;
    }
}

#endif // AVL_TREE_HPP