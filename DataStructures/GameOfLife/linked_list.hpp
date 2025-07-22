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

		bool Empty() const noexcept;
		size_t Size() const noexcept;

		bool operator==(const LinkedList& rhs) const noexcept;
		bool operator!=(const LinkedList& rhs) const noexcept;

		/* ----------------------------------------------------------------------- */
		/*  Forward iteration                                                     */
		/* ----------------------------------------------------------------------- */
		iterator       begin();
		iterator       end();

		const_iterator begin() const;
		const_iterator end()   const;

		const_iterator cbegin() const;
		const_iterator cend()   const;

		/* ----------------------------------------------------------------------- */
		/*  Reverse iteration (optional)                                           */
		/* ----------------------------------------------------------------------- */
		iterator       rbegin();
		iterator       rend();

		const_iterator rbegin() const;
		const_iterator rend()   const;

		const_iterator crbegin() const;
		const_iterator crend()   const;

	private:
		ListNode<T>* head_{ nullptr };
		ListNode<T>* tail_{ nullptr };
		size_t size_{ 0 };

		ListNode<T>* CreateNode(const T& data, ListNode<T>* next = nullptr, ListNode<T>* previous = nullptr);
	};



}
#endif