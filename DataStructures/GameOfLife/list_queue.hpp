#ifndef list_queue_HPP
#define list_queue_HPP

#include "iqueue.hpp"
#include "linked_list.hpp"

namespace data_structures
{
	template <class T>
	class ListQueue final : public IQueue<T>
	{
	public:
		ListQueue() = default;
		ListQueue(const ListQueue& copy);
		ListQueue& operator=(const ListQueue& rhs);

		ListQueue(ListQueue&& copy) noexcept;
		ListQueue& operator=(ListQueue&& rhs) noexcept;

		~ListQueue() override = default;

		void Enqueue(T data) override;
		T Dequeue() override;

		T& Front() override;

		void Clear() noexcept override;
		size_t Size() const noexcept override;
		bool IsEmpty() const noexcept override;

	private:
		LinkedList<T> queue_;
	};


}

#endif
