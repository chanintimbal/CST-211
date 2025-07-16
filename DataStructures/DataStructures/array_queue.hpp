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
		ArrayQueue();
		explicit ArrayQueue(size_t length);
		~ArrayQueue() override = default;

		ArrayQueue(const ArrayQueue& copy);
		ArrayQueue& operator=(const ArrayQueue& rhs);
		ArrayQueue(ArrayQueue&& move) noexcept;
		ArrayQueue& operator=(ArrayQueue&& rhs) noexcept;

		void Enqueue(T data) override;
		T Dequeue() override;
		T& Front() override;
		bool IsFull() const noexcept;
		void Clear() noexcept override;

		size_t Size() const noexcept override;
		bool IsEmpty() const noexcept override;

		size_t QueueLength() const noexcept;

	private:
		Array<T> queue_;
		size_t front_{ 0 };
		size_t back_{ 0 };
		size_t count_{ 0 };
	};

	template <typename T>
	ArrayQueue<T>::ArrayQueue() : queue_(4) {}

	template <typename T>
	ArrayQueue<T>::ArrayQueue(size_t length) : queue_(length) {}

	template <typename T>
	ArrayQueue<T>::ArrayQueue(const ArrayQueue& copy) : queue_()
	{
		*this = copy;
	}

	template <typename T>
	ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			queue_ = rhs.queue_;
			front_ = rhs.front_;
			back_ = rhs.back_;
			count_ = rhs.count_;
		}
		return *this;
	}

	template <typename T>
	ArrayQueue<T>::ArrayQueue(ArrayQueue&& move) noexcept
	{
		*this = std::move(move);
	}

	template <typename T>
	ArrayQueue<T>& ArrayQueue<T>::operator=(ArrayQueue&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			queue_ = std::move(rhs.queue_);
			front_ = rhs.front_;
			back_ = rhs.back_;
			count_ = rhs.count_;
		}
		return *this;
	}

	template <typename T>
	void ArrayQueue<T>::Enqueue(T data)
	{
		if (IsFull())
			throw AdtException("Queue is Full.");

		queue_[back_] = data;
		back_++;
		count_++;
		
	}

	template <typename T>
	T ArrayQueue<T>::Dequeue()
	{
		if (IsEmpty())
			throw AdtException("Queue is empty");

		auto temp = queue_[front_];
		front_++;
		count_--;
		return temp;
	}

	template <typename T>
	T& ArrayQueue<T>::Front()
	{
		//Rainy day and sunny day tests
		if (IsEmpty())
			throw AdtException("Queue is empty.");
		return queue_[front_];
	}

	template <typename T>
	bool ArrayQueue<T>::IsFull() const noexcept
	{
		return count_ == queue_.size();
	}

	template <typename T>
	void ArrayQueue<T>::Clear() noexcept
	{
		front_ = 0;
		count_ = 0;
		back_ = 0;
	}

	template <typename T>
	size_t ArrayQueue<T>::Size() const noexcept
	{
		return count_;
	}

	template <typename T>
	bool ArrayQueue<T>::IsEmpty() const noexcept
	{
		return count_ == 0;
	}

	template <typename T>
	size_t ArrayQueue<T>::QueueLength() const noexcept
	{
		return queue_.size();
	}
}
#endif // array_queue_HPP
