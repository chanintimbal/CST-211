#ifndef LIST_STACK_HPP
#define LIST_STACK_HPP

#include "istack.hpp"
#include "linked_list.hpp"
#include "adt_exception.hpp"

namespace data_structures
{
	template <class T>
	class ListStack final : public IStack<T>
	{
	public:
		ListStack() = default;
		ListStack(const ListStack& copy);
		ListStack& operator=(const ListStack& rhs);
		ListStack(ListStack&& copy) noexcept;
		ListStack& operator=(ListStack&& rhs) noexcept;
		~ListStack() override = default;

		T Pop() override;
		T Peek() const override;
		void Push(T data) override;
		void Clear() noexcept override;
		bool IsEmpty() const noexcept override;
		size_t Size() const noexcept override;

	private:
		LinkedList<T> stack_;
	};

	template <class T>
	ListStack<T>::ListStack(const ListStack& copy)
		: stack_(copy.stack_)
	{
	}

	template <class T>
	ListStack<T>& ListStack<T>::operator=(const ListStack& rhs)
	{
		if (this != &rhs)
		{
			stack_ = rhs.stack_;
		}
		return *this;
	}

	template <class T>
	ListStack<T>::ListStack(ListStack&& copy) noexcept
		: stack_(std::move(copy.stack_))
	{
	}

	template <class T>
	ListStack<T>& ListStack<T>::operator=(ListStack&& rhs) noexcept
	{
		if (this != &rhs)
		{
			stack_ = std::move(rhs.stack_);
		}
		return *this;
	}

	template <class T>
	void ListStack<T>::Push(T data)
	{
		stack_.Prepend(data);
	}

	template <class T>
	T ListStack<T>::Pop()
	{
		if (stack_.IsEmpty())
			throw AdtException("Stack is empty, nothing to pop");
		T value = stack_.First();
		stack_.RemoveFirst();
		return value;
	}

	template <class T>
	T ListStack<T>::Peek() const
	{
		if (stack_.IsEmpty())
			throw AdtException("Stack is empty, nothing to peek");
		return stack_.First();
	}

	template <class T>
	void ListStack<T>::Clear() noexcept
	{
		stack_.Clear();
	}

	template <class T>
	bool ListStack<T>::IsEmpty() const noexcept
	{
		return stack_.IsEmpty();
	}

	template <class T>
	size_t ListStack<T>::Size() const noexcept
	{
		return stack_.Size();
	}
}

#endif
