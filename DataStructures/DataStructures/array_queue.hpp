#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

#include "iqueue.hpp"
#include "array.hpp"

namespace data_structures
{
	template <typename  T>
	class ArrayQueue final : public IQueue<T>
	{
	public:
		ArrayQueue() = default;
		explicit ArrayQueue(size_t length);

		ArrayQueue(const ArrayQueue& copy);
		ArrayQueue& operator=(const ArrayQueue& rhs);
		ArrayQueue(ArrayQueue&& copy) noexcept;
		ArrayQueue& operator=(ArrayQueue&& rhs) noexcept;

		void Enqueue(T data) override;
		T Dequeue() override;
		T& Front() override;
		bool IsFull() const noexcept;
		void Clear() noexcept override;

		~ArrayQueue() override = default;
		size_t Size() const noexcept override;
		bool IsEmpty() const noexcept override;

		size_t QueueLength() const noexcept;

	private:
		Array<T> queue_;
		size_t front_{ 0 };
		size_t back_{ 0 };
		size_t count_{ 0 };
	};
	
}
#endif // array_queue_HPP
