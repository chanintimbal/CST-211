#ifndef UNDO_REDO_HPP
#define UNDO_REDO_HPP

#include "list_stack.hpp"
#include "adt_exception.hpp"

namespace data_structures
{
	template <class T>
	class UndoRedo final
	{
	public:
		explicit UndoRedo(size_t max_history);
		UndoRedo(const UndoRedo& copy);
		UndoRedo& operator=(const UndoRedo& rhs);
		UndoRedo(UndoRedo&& copy) noexcept;
		UndoRedo& operator=(UndoRedo&& rhs) noexcept;
		~UndoRedo() = default;

		void Do(const T& action);
		T Undo();
		T Redo();
		bool CanUndo() const noexcept;
		bool CanRedo() const noexcept;
		void Clear() noexcept;
		size_t MaxHistory() const noexcept;
		size_t UndoSize() const noexcept;
		size_t RedoSize() const noexcept;

	private:
		size_t max_history_;
		ListStack<T> undo_;
		ListStack<T> redo_;
		void TrimUndoIfNeeded();
	};

	template <class T>
	UndoRedo<T>::UndoRedo(size_t max_history)
		: max_history_(max_history)
	{
		if (max_history_ == 0)
			throw AdtException("Max history must be greater than 0");
	}

	template <class T>
	UndoRedo<T>::UndoRedo(const UndoRedo& copy)
		: max_history_(copy.max_history_), undo_(copy.undo_), redo_(copy.redo_)
	{
	}

	template <class T>
	UndoRedo<T>& UndoRedo<T>::operator=(const UndoRedo& rhs)
	{
		if (this != &rhs)
		{
			max_history_ = rhs.max_history_;
			undo_ = rhs.undo_;
			redo_ = rhs.redo_;
		}
		return *this;
	}

	template <class T>
	UndoRedo<T>::UndoRedo(UndoRedo&& copy) noexcept
		: max_history_(copy.max_history_), undo_(std::move(copy.undo_)), redo_(std::move(copy.redo_))
	{
		copy.max_history_ = 0;
	}

	template <class T>
	UndoRedo<T>& UndoRedo<T>::operator=(UndoRedo&& rhs) noexcept
	{
		if (this != &rhs)
		{
			max_history_ = rhs.max_history_;
			undo_ = std::move(rhs.undo_);
			redo_ = std::move(rhs.redo_);
			rhs.max_history_ = 0;
		}
		return *this;
	}

	template <class T>
	void UndoRedo<T>::Do(const T& action)
	{
		TrimUndoIfNeeded();
		undo_.Push(action);
		redo_.Clear();
	}

	template <class T>
	T UndoRedo<T>::Undo()
	{
		if (!CanUndo())
			throw AdtException("Nothing to undo");

		T action = undo_.Pop();
		redo_.Push(action);
		return action;
	}

	template <class T>
	T UndoRedo<T>::Redo()
	{
		if (!CanRedo())
			throw AdtException("Nothing to redo");

		T action = redo_.Pop();
		undo_.Push(action);
		TrimUndoIfNeeded();
		return action;
	}

	template <class T>
	bool UndoRedo<T>::CanUndo() const noexcept
	{
		return !undo_.IsEmpty();
	}

	template <class T>
	bool UndoRedo<T>::CanRedo() const noexcept
	{
		return !redo_.IsEmpty();
	}

	template <class T>
	void UndoRedo<T>::Clear() noexcept
	{
		undo_.Clear();
		redo_.Clear();
	}

	template <class T>
	size_t UndoRedo<T>::MaxHistory() const noexcept
	{
		return max_history_;
	}

	template <class T>
	size_t UndoRedo<T>::UndoSize() const noexcept
	{
		return undo_.Size();
	}

	template <class T>
	size_t UndoRedo<T>::RedoSize() const noexcept
	{
		return redo_.Size();
	}

	template <class T>
	void UndoRedo<T>::TrimUndoIfNeeded()
	{
		while (undo_.Size() >= max_history_)
		{
			ListStack<T> temp;
			size_t n = undo_.Size();
			for (size_t i = 0; i < n - 1; ++i)
				temp.Push(undo_.Pop());

			undo_.Pop();

			while (!temp.IsEmpty())
				undo_.Push(temp.Pop());
		}
	}
}

#endif
