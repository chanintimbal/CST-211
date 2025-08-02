#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "adt_exception.hpp"
#include "list_node.hpp"
#include "list_iterator.hpp"

namespace data_structures
{
	template <class T>
	class LinkedList final
	{
	public:
		using iterator = ListIterator<T>;
		using const_iterator = ListIterator<T>;

		LinkedList() = default;

		LinkedList(const LinkedList& copy);
		LinkedList(LinkedList&& copy) noexcept(false);
		~LinkedList();

		LinkedList& operator=(const LinkedList& rhs) noexcept(false);
		LinkedList& operator=(LinkedList&& rhs) noexcept(false);

		explicit operator bool() const;

		void Append(const T& data);
		void Prepend(const T& data);
		void RemoveLast();
		void RemoveFirst();
		void Remove(const T& data);
		void InsertAfter(const T& data, const T& after);
		void InsertBefore(const T& data, const T& before);
		void Clear() noexcept;

		T& Last();
		T Last() const;
		T& First();
		T First() const;

		ListNode<T>* Head() const noexcept;
		ListNode<T>* Tail() const noexcept;

		bool IsEmpty() const noexcept;
		size_t Size() const noexcept;

		bool operator==(const LinkedList& rhs) const noexcept;
		bool operator!=(const LinkedList& rhs) const noexcept;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		iterator rbegin();
		iterator rend();
		const_iterator rbegin() const;
		const_iterator rend() const;
		const_iterator crbegin() const;
		const_iterator crend() const;

	private:
		ListNode<T>* head_{ nullptr };
		ListNode<T>* tail_{ nullptr };
		size_t size_{ 0 };

		ListNode<T>* CreateNode(const T& data, ListNode<T>* next = nullptr, ListNode<T>* previous = nullptr);
	};

	// Copy constructor
	template <class T>
	LinkedList<T>::LinkedList(const LinkedList& copy)
	{
		for (auto it = copy.begin(); it != copy.end(); ++it)
			Append(*it);
	}

	// Move constructor
	template <class T>
	LinkedList<T>::LinkedList(LinkedList&& copy) noexcept(false)
		: head_{ copy.head_ }, tail_{ copy.tail_ }, size_{ copy.size_ }
	{
		copy.head_ = copy.tail_ = nullptr;
		copy.size_ = 0;
	}

	// Destructor
	template <class T>
	LinkedList<T>::~LinkedList()
	{
		Clear();
	}

	// Copy assignment
	template <class T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) noexcept(false)
	{
		if (this != &rhs)
		{
			Clear();
			for (auto it = rhs.begin(); it != rhs.end(); ++it)
				Append(*it);
		}
		return *this;
	}

	// Move assignment
	template <class T>
	LinkedList<T>& LinkedList<T>::operator=(LinkedList&& rhs) noexcept(false)
	{
		if (this != &rhs)
		{
			Clear();
			head_ = rhs.head_;
			tail_ = rhs.tail_;
			size_ = rhs.size_;
			rhs.head_ = rhs.tail_ = nullptr;
			rhs.size_ = 0;
		}
		return *this;
	}

	template <class T>
	LinkedList<T>::operator bool() const
	{
		return !IsEmpty();
	}

	template <class T>
	void LinkedList<T>::Append(const T& data)
	{
		auto node = CreateNode(data, nullptr, tail_);
		if (!head_)
			head_ = node;
		else
			tail_->Next(node);
		tail_ = node;
		++size_;
	}

	template <class T>
	void LinkedList<T>::Prepend(const T& data)
	{
		auto node = CreateNode(data, head_, nullptr);
		if (!tail_)
			tail_ = node;
		else
			head_->Prev(node);
		head_ = node;
		++size_;
	}

	template <class T>
	void LinkedList<T>::RemoveLast()
	{
		if (!tail_)
			throw AdtException("List is empty");
		auto toDelete = tail_;
		tail_ = tail_->Prev();
		if (tail_)
			tail_->Next(nullptr);
		else
			head_ = nullptr;
		delete toDelete;
		--size_;
	}

	template <class T>
	void LinkedList<T>::RemoveFirst()
	{
		if (!head_)
			throw AdtException("List is empty");
		auto toDelete = head_;
		head_ = head_->Next();
		if (head_)
			head_->Prev(nullptr);
		else
			tail_ = nullptr;
		delete toDelete;
		--size_;
	}

	template <class T>
	void LinkedList<T>::Remove(const T& data)
	{
		for (auto* node = head_; node; node = node->Next())
		{
			if (node->Value() == data)
			{
				if (node == head_) RemoveFirst();
				else if (node == tail_) RemoveLast();
				else
				{
					node->Prev()->Next(node->Next());
					node->Next()->Prev(node->Prev());
					delete node;
					--size_;
				}
				return;
			}
		}
		throw AdtException("Element not found");
	}

	template <class T>
	void LinkedList<T>::InsertAfter(const T& data, const T& after)
	{
		for (auto* node = head_; node; node = node->Next())
		{
			if (node->Value() == after)
			{
				if (node == tail_)
				{
					Append(data);
				}
				else
				{
					auto newNode = CreateNode(data, node->Next(), node);
					node->Next()->Prev(newNode);
					node->Next(newNode);
					++size_;
				}
				return;
			}
		}
		throw AdtException("Insertion target not found");
	}

	template <class T>
	void LinkedList<T>::InsertBefore(const T& data, const T& before)
	{
		for (auto* node = head_; node; node = node->Next())
		{
			if (node->Value() == before)
			{
				if (node == head_)
				{
					Prepend(data);
				}
				else
				{
					auto newNode = CreateNode(data, node, node->Prev());
					node->Prev()->Next(newNode);
					node->Prev(newNode);
					++size_;
				}
				return;
			}
		}
		throw AdtException("Insertion target not found");
	}

	template <class T>
	void LinkedList<T>::Clear() noexcept
	{
		while (head_)
		{
			auto temp = head_;
			head_ = head_->Next();
			delete temp;
		}
		tail_ = nullptr;
		size_ = 0;
	}

	template <class T>
	T& LinkedList<T>::Last()
	{
		if (!tail_)
			throw AdtException("List is empty");
		return tail_->Value();
	}

	template <class T>
	T LinkedList<T>::Last() const
	{
		if (!tail_)
			throw AdtException("List is empty");
		return tail_->Value();
	}

	template <class T>
	T& LinkedList<T>::First()
	{
		if (!head_)
			throw AdtException("List is empty");
		return head_->Value();
	}

	template <class T>
	T LinkedList<T>::First() const
	{
		if (!head_)
			throw AdtException("List is empty");
		return head_->Value();
	}

	template <class T>
	ListNode<T>* LinkedList<T>::Head() const noexcept
	{
		return head_;
	}

	template <class T>
	ListNode<T>* LinkedList<T>::Tail() const noexcept
	{
		return tail_;
	}

	template <class T>
	bool LinkedList<T>::IsEmpty() const noexcept
	{
		return size_ == 0;
	}

	template <class T>
	size_t LinkedList<T>::Size() const noexcept
	{
		return size_;
	}

	template <class T>
	bool LinkedList<T>::operator==(const LinkedList& rhs) const noexcept
	{
		if (size_ != rhs.size_)
			return false;
		auto it1 = begin(), it2 = rhs.begin();
		while (it1 != end())
		{
			if (*it1 != *it2)
				return false;
			++it1;
			++it2;
		}
		return true;
	}

	template <class T>
	bool LinkedList<T>::operator!=(const LinkedList& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	// Iterators
	template <class T>
	typename LinkedList<T>::iterator LinkedList<T>::begin()
	{
		return iterator(head_, tail_, true);
	}

	template <class T>
	typename LinkedList<T>::iterator LinkedList<T>::end()
	{
		return iterator(nullptr, tail_, true);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::begin() const
	{
		return const_iterator(head_, tail_, true);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::end() const
	{
		return const_iterator(nullptr, tail_, true);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const
	{
		return const_iterator(head_, tail_, true);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::cend() const
	{
		return const_iterator(nullptr, tail_, true);
	}

	template <class T>
	typename LinkedList<T>::iterator LinkedList<T>::rbegin()
	{
		return iterator(tail_, head_, false);
	}

	template <class T>
	typename LinkedList<T>::iterator LinkedList<T>::rend()
	{
		return iterator(nullptr, head_, false);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::rbegin() const
	{
		return const_iterator(tail_, head_, false);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::rend() const
	{
		return const_iterator(nullptr, head_, false);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::crbegin() const
	{
		return const_iterator(tail_, head_, false);
	}

	template <class T>
	typename LinkedList<T>::const_iterator LinkedList<T>::crend() const
	{
		return const_iterator(nullptr, head_, false);
	}

	template <class T>
	ListNode<T>* LinkedList<T>::CreateNode(const T& data, ListNode<T>* next, ListNode<T>* previous)
	{
		return new ListNode<T>(data, next, previous);
	}
}

#endif
