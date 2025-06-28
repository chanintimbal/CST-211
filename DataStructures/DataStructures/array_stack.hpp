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
		size_t size_;
		Array<T> stack_;
		size_t top_{ 0 };
	};
	
}
#endif // array_stack_HPP
