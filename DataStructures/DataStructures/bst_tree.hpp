#ifndef BST_TREE_HPP
#define BST_TREE_HPP

#include "bst_base.hpp"
#include "bst_node.hpp"
#include "bst_iterator.hpp"
#include "list_queue.hpp"
#include <functional>
#include <utility>

namespace data_structures
{
	template <class K, class V>
	class BstTree final : public BinarySearchTreeBase<K, V, BstTree<K, V>, BstNode<K, V>>
	{
		using Node = BstNode<K, V>;
		using Base = BinarySearchTreeBase<K, V, BstTree, BstNode<K, V>>;

	public:
		using iterator = BstIterator<K, V, false>;
		using const_iterator = BstIterator<K, V, true>;

		BstTree() = default;
		~BstTree() override;

		BstTree(const BstTree& copy);
		BstTree& operator=(const BstTree& rhs);
		BstTree(BstTree&& copy) noexcept;
		BstTree& operator=(BstTree&& rhs) noexcept;

		std::pair<V&, bool> InsertImpl(const K& key, const V& value);
		void RemoveImpl(const K& key);

		V& operator[](const K& key);

		iterator begin() noexcept;
		iterator end() noexcept;

		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;

		const_iterator cbegin() const noexcept;
		static const_iterator cend() noexcept;

	private:
		std::pair<V&, bool> Insert(Node*& cur, const K& key, const V& value, Node* parent);
		void Remove(Node*& cur, const K& key);

		V& Lookup(Node* cur, const K& key) const;
		V* LookupPtr(Node* cur, const K& key) const;
	};

	template <class K, class V>
	BstTree<K, V>::~BstTree()
	{
		this->Clear();
	}

	template <class K, class V>
	BstTree<K, V>::BstTree(const BstTree& copy)
	{
		this->Copy(copy.Root());
	}

	template <class K, class V>
	BstTree<K, V>& BstTree<K, V>::operator=(const BstTree& rhs)
	{
		if (this != &rhs)
		{
			this->Clear();
			this->Copy(rhs.Root());
		}
		return *this;
	}

	template <class K, class V>
	BstTree<K, V>::BstTree(BstTree&& copy) noexcept
	{
		this->Root() = copy.Root();
		copy.Root() = nullptr;
	}

	template <class K, class V>
	BstTree<K, V>& BstTree<K, V>::operator=(BstTree&& rhs) noexcept
	{
		if (this != &rhs)
		{
			this->Clear();
			std::swap(this->Root(), rhs.Root());
		}
		return *this;
	}

	template <class K, class V>
	std::pair<V&, bool> BstTree<K, V>::InsertImpl(const K& key, const V& value)
	{
		return Insert(this->Root(), key, value, nullptr);
	}

	template <class K, class V>
	void BstTree<K, V>::RemoveImpl(const K& key)
	{
		Remove(this->Root(), key);
	}

	template <class K, class V>
	V& BstTree<K, V>::operator[](const K& key)
	{
		return Base::insert(key, V{}).first;
	}

	template <class K, class V>
	typename BstTree<K, V>::iterator BstTree<K, V>::begin() noexcept
	{
		return iterator(this->Min(this->Root()));
	}

	template <class K, class V>
	typename BstTree<K, V>::iterator BstTree<K, V>::end() noexcept
	{
		return iterator(nullptr);
	}

	template <class K, class V>
	typename BstTree<K, V>::const_iterator BstTree<K, V>::begin() const noexcept
	{
		return const_iterator(this->Min(this->Root()));
	}

	template <class K, class V>
	typename BstTree<K, V>::const_iterator BstTree<K, V>::end() const noexcept
	{
		return const_iterator(nullptr);
	}

	template <class K, class V>
	typename BstTree<K, V>::const_iterator BstTree<K, V>::cbegin() const noexcept
	{
		return const_iterator(this->Min(this->Root()));
	}

	template <class K, class V>
	typename BstTree<K, V>::const_iterator BstTree<K, V>::cend() noexcept
	{
		return const_iterator(nullptr);
	}

	template <class K, class V>
	std::pair<V&, bool> BstTree<K, V>::Insert(Node*& cur, const K& key, const V& value, Node* parent)
	{
		if (!cur)
		{
			cur = new Node(key, value);
			cur->Parent(parent);
			return { cur->Value(), true };
		}
		if (key < cur->Key())
			return Insert(cur->Left(), key, value, cur);
		else if (key > cur->Key())
			return Insert(cur->Right(), key, value, cur);
		else
			return { cur->Value(), false };  // key exists
	}

	template <class K, class V>
	void BstTree<K, V>::Remove(Node*& cur, const K& key)
	{
		if (!cur) return;

		if (key < cur->Key())
		{
			Remove(cur->Left(), key);
		}
		else if (key > cur->Key())
		{
			Remove(cur->Right(), key);
		}
		else
		{
			if (!cur->Left() && !cur->Right())
			{
				delete cur;
				cur = nullptr;
			}
			else if (!cur->Left())
			{
				Node* temp = cur;
				cur = cur->Right();
				cur->Parent(temp->Parent());
				delete temp;
			}
			else if (!cur->Right())
			{
				Node* temp = cur;
				cur = cur->Left();
				cur->Parent(temp->Parent());
				delete temp;
			}
			else
			{
				Node* successor = this->MinNode(cur->Right());
				cur->Key(successor->Key());
				cur->Value() = successor->Value();
				Remove(cur->Right(), successor->Key());
			}
		}
	}

	template <class K, class V>
	V& BstTree<K, V>::Lookup(Node* cur, const K& key) const
	{
		V* valPtr = LookupPtr(cur, key);
		if (!valPtr) throw AdtException("Key not found");
		return *valPtr;
	}

	template <class K, class V>
	V* BstTree<K, V>::LookupPtr(Node* cur, const K& key) const
	{
		while (cur)
		{
			if (key < cur->Key())
				cur = cur->Left();
			else if (key > cur->Key())
				cur = cur->Right();
			else
				return &cur->Value();
		}
		return nullptr;
	}
}

#endif
