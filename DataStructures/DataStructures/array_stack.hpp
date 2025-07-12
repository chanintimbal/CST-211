#ifndef ARRAY_STACK_HPP
#define ARRAY_STACK_HPP

#include "istack.hpp"
#include "array.hpp"
#include "adt_exception.hpp"

namespace data_structures
{
	template <typename T>
	class ArrayStack final : public IStack<T>
	{
	public:
		ArrayStack();
		explicit ArrayStack(size_t max_size);
		~ArrayStack() override = default;

		ArrayStack(const ArrayStack& copy);
		ArrayStack& operator=(const ArrayStack& rhs);
		ArrayStack(ArrayStack&& copy) noexcept;
		ArrayStack& operator=(ArrayStack&& rhs) noexcept;

		T Pop() override;
		T Peek() const override;
		void Push(T data) override;
		bool IsFull() const noexcept;
		void Clear() noexcept override;
		bool IsEmpty() const noexcept override;
		size_t Size() const noexcept override;
		size_t Capacity() const noexcept;

	private:
		Array<T> stack_;
		size_t top_{ 0 };
	};

	template <typename T>
	ArrayStack<T>::ArrayStack() : stack_(4)
	{
	}

	template <typename T>
	ArrayStack<T>::ArrayStack(size_t max_size) : stack_(max_size)
	{
	}

	template <typename T>
	ArrayStack<T>::ArrayStack(const ArrayStack& copy)
	{
		*this = copy;
	}

	template <typename T>
	ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack& rhs)
	{
		//stack = stack2
		if (this != &rhs)
		{
			stack_ = rhs.stack_;
			top_ = rhs.top_;
		}
		return *this;
	}

	template <typename T>
	ArrayStack<T>::ArrayStack(ArrayStack&& copy) noexcept
	{
		*this = std::move(copy);
	}

	template <typename T>
	ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack&& rhs) noexcept
	{
		if (this != &rhs)
		{
			top_ = rhs.top_;
			stack_ = std::move(rhs.stack_);
		}
		return *this;
	}

	template <typename T>
	T ArrayStack<T>::Pop()
	{
		if (!IsEmpty())
		{
			T temp = stack_[--top_];
			return temp;
		}
		throw AdtException("stack is empty, nothing to pop");
	}

	template <typename T>
	T ArrayStack<T>::Peek() const
	{
		if (!IsEmpty())
		{
			return stack_[top_ - 1];
		}
		throw AdtException("stack is empty, nothing to peek");
	}

	template <typename T>
	void ArrayStack<T>::Push(T data)
	{
		if (!IsFull())
		{
			stack_[top_++] = data;
		}
		else throw AdtException("Stack is full, unable to push");
	}

	template <typename T>
	bool ArrayStack<T>::IsFull() const noexcept
	{
		return stack_.size() == SIZE_MAX;
	}

	template <typename T>
	void ArrayStack<T>::Clear() noexcept
	{
		top_ = 0;
	}

	template <typename T>
	bool ArrayStack<T>::IsEmpty() const noexcept
	{
		return stack_.size() == 0;
	}

	template <typename T>
	size_t ArrayStack<T>::Size() const noexcept
	{
		// How many elements are in the stack
		return top_;
	}

	template <typename T>
	size_t ArrayStack<T>::Capacity() const noexcept
	{
		// Is the actual array size
		return stack_.size();
	}
}
#endif // array_stack_HPP
