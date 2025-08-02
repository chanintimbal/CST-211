#ifndef LIST_QUEUE_HPP
#define LIST_QUEUE_HPP

#include "iqueue.hpp"
#include "linked_list.hpp"
#include "adt_exception.hpp"

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

	template <class T>
	ListQueue<T>::ListQueue(const ListQueue& copy)
		: queue_(copy.queue_)
	{
	}

	template <class T>
	ListQueue<T>& ListQueue<T>::operator=(const ListQueue& rhs)
	{
		if (this != &rhs)
		{
			queue_ = rhs.queue_;
		}
		return *this;
	}

	template <class T>
	ListQueue<T>::ListQueue(ListQueue&& copy) noexcept
		: queue_(std::move(copy.queue_))
	{
	}

	template <class T>
	ListQueue<T>& ListQueue<T>::operator=(ListQueue&& rhs) noexcept
	{
		if (this != &rhs)
		{
			queue_ = std::move(rhs.queue_);
		}
		return *this;
	}

	template <class T>
	void ListQueue<T>::Enqueue(T data)
	{
		queue_.Append(data);
	}

	template <class T>
	T ListQueue<T>::Dequeue()
	{
		if (queue_.IsEmpty())
			throw AdtException("Queue is empty, nothing to dequeue");
		T value = queue_.First();
		queue_.RemoveFirst();
		return value;
	}

	template <class T>
	T& ListQueue<T>::Front()
	{
		if (queue_.IsEmpty())
			throw AdtException("Queue is empty, nothing at front");
		return queue_.First();
	}

	template <class T>
	void ListQueue<T>::Clear() noexcept
	{
		queue_.Clear();
	}

	template <class T>
	size_t ListQueue<T>::Size() const noexcept
	{
		return queue_.Size();
	}

	template <class T>
	bool ListQueue<T>::IsEmpty() const noexcept
	{
		return queue_.IsEmpty();
	}
}

#endif
