#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

#include "node.hpp"

namespace data_structures
{
	template <class T>
	class ListNode final : public Node<T>
	{
	public:
		ListNode() = delete;
		explicit ListNode(const T& data, ListNode* next = nullptr, ListNode* previous = nullptr);

		ListNode(const ListNode& copy);
		ListNode& operator=(const ListNode& rhs);

		ListNode(ListNode&& copy) noexcept;
		ListNode& operator=(ListNode&& rhs) noexcept;

		ListNode* Next() noexcept;
		ListNode* Next() const noexcept;
		ListNode* Prev() noexcept;
		ListNode* Prev() const noexcept;

		void Next(ListNode* next) noexcept;
		void Prev(ListNode* previous) noexcept;

		bool operator==(const ListNode& rhs) const noexcept;
		bool operator!=(const ListNode& rhs) const noexcept;

		~ListNode() override = default;

	private:
		ListNode* next_{ nullptr };
		ListNode* prev_{ nullptr };
	};

	template <class T>
	ListNode<T>::ListNode(const T& data, ListNode* next, ListNode* previous)
		: Node<T>(data), next_{ next }, prev_{ previous } {}

	template <class T>
	ListNode<T>::ListNode(const ListNode& copy)
		: Node<T>(copy), next_{ copy.next_ }, prev_{ copy.prev_ } {}

	template <class T>
	ListNode<T>& ListNode<T>::operator=(const ListNode& rhs)
	{
		if (this != &rhs)
		{
			Node<T>::operator=(rhs);
			next_ = rhs.next_;
			prev_ = rhs.prev_;
		}
		return *this;
	}

	template <class T>
	ListNode<T>::ListNode(ListNode&& copy) noexcept
		: Node<T>(std::move(copy)), next_{ copy.next_ }, prev_{ copy.prev_ }
	{
		copy.next_ = nullptr;
		copy.prev_ = nullptr;
	}

	template <class T>
	ListNode<T>& ListNode<T>::operator=(ListNode&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Node<T>::operator=(std::move(rhs));
			next_ = rhs.next_;
			prev_ = rhs.prev_;
			rhs.next_ = nullptr;
			rhs.prev_ = nullptr;
		}
		return *this;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Next() noexcept
	{
		return next_;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Next() const noexcept
	{
		return next_;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Prev() noexcept
	{
		return prev_;
	}

	template <class T>
	ListNode<T>* ListNode<T>::Prev() const noexcept
	{
		return prev_;
	}

	template <class T>
	void ListNode<T>::Next(ListNode* next) noexcept
	{
		next_ = next;
	}

	template <class T>
	void ListNode<T>::Prev(ListNode* previous) noexcept
	{
		prev_ = previous;
	}

	template <class T>
	bool ListNode<T>::operator==(const ListNode& rhs) const noexcept
	{
		return this == &rhs ||
			(Node<T>::operator==(rhs) && next_ == rhs.next_ && prev_ == rhs.prev_);
	}

	template <class T>
	bool ListNode<T>::operator!=(const ListNode& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}

#endif