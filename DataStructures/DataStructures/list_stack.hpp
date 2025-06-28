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
		~ListStack() override;

		T Pop() override;
		T Peek() const override;
		void Push(T data) override;
		void Clear() noexcept override;
		bool IsEmpty() const noexcept override;
		size_t Size() const noexcept override;

	private:
		LinkedList<T> stack_;
	};

}
#endif