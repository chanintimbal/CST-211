#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "adt_exception.hpp"

namespace data_structures
{
	template <class T>
	class Array final
	{
	public:
		using iterator = T*;
		using const_iterator = const T*;

		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using difference_type = std::ptrdiff_t;

		explicit Array() = default;
		~Array();
		explicit Array(size_t length); // can throw exceptions
		explicit Array(const T* storage, const size_t& length);

		Array(const Array& copy);
		Array& operator=(const Array& rhs);
		Array(Array&& copy) noexcept;
		Array& operator=(Array&& rhs) noexcept;

		T& operator[](const size_t& index);
		const T& operator[](const size_t& index) const;

		explicit operator bool() const noexcept;
		bool operator==(const Array& rhs) const noexcept;
		bool operator!=(const Array& rhs) const noexcept;

		//std vector-like functions
		size_t size()  const noexcept;
		bool empty() const noexcept;

		void resize(size_t newSize);
		void clear();

		/* iterators ---------------------------------------------------------- */
		iterator       begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		iterator       end()   noexcept;
		const_iterator end()   const noexcept;
		const_iterator cend()  const noexcept;

		/* data access -------------------------------------------------------- */
		T* data() noexcept { return storage_; }
		const T* data() const noexcept { return storage_; }

	private:
		T* storage_{ nullptr };
		size_t length_{ 0 };

		void Length(const size_t& length);
		T* AllocateArray(const size_t& length);
	};
	template<class T>
	inline Array<T>::~Array()
	{
		delete[] storage_;
		storage_ = nullptr;
	}
	template<class T>
	inline Array<T>::Array(size_t length) : length_(length)
	{
		T* storage = nullptr;
		try
		{
			storage = new T[length]{};
		}
		catch (const std::bad_alloc& ex)
		{
			delete[] storage;
			storage = nullptr;
			throw AdtException(ex.what());
		}
		storage_ = storage;
	}

	template<class T>
	inline Array<T>::Array(const T* storage, const size_t& length) : length_(length)
	{
		T* storage = nullptr;
		try
		{
			storage = new T[length]{};
		}
		catch (const std::bad_alloc& ex)
		{
			delete[] storage;
			storage = nullptr;
			throw AdtException(ex.what());
		}
		storage_ = storage;

		for (auto i = 0ull; i < length; ++i) {
			storage_[i] = storage[i];
		}
	}
	template<class T>
	inline Array<T>::Array(const Array& copy)
	{
		*this = copy;
	}

	template<class T>
	inline Array& Array<T>::operator=(const Array& rhs)
	{
		//myarray = someOtherArray
		if (this != &rhs)
		{
			T* new_storage = AllocateArray(rhs.length_);

			for (auto i = 0ull; i < rhs.length_; ++i)
			{
				new_storage[i] = rhs.storage_[i];
			}
			//Delete old storage and update the members
			delete[] storage_;
			storage_ = new_storage;
			length_ = rhs.length_;
		}

	}
	template<class T>
	inline Array<T>::Array(Array&& copy) noexcept : storage_(copy.storage_), length_(copy.length_)
	{
		copy.storage_ = nullptr;
		copy.length_ = 0;
	}
	template<class T>
	inline Array& Array<T>::operator=(Array&& rhs) noexcept
	{
		if (this != &rhs)
		{
			delete[] storage_;
			storage_ = nullptr;

			storage_ = rhs.storage_;
			length + rhs.length_;

			rhs.storage_ = nullptr;
			rhs.length_ = 0;
		}
	}
	template<class T>
	inline T& Array<T>::operator[](const size_t& index)
	{
		if (index >= length_)
			throw AdtException(what: "Outside the bounds of the array");

		return storage_[index];
	}

	template<class T>
	inline const T& Array<T>::operator[](const size_t& index) const
	{
		if (index >= length_)
			throw AdtException(what: "Outside the bounds of the array");

		return storage_[index];
	}

	template<class T>
	inline Array<T>::operator bool() const noexcept
	{
		//if (array) {do something}
		//return (length_ != 0);
		return storage_ != nullptr;
	}

	template<class T>
	inline bool Array<T>::operator==(const Array& rhs) const noexcept
	{
		if (length_ == rhs.length_)
		{
			for (auto i 0ull; i < length_; ++i)
			{
				if (storage_[i] != rhs.storage_[i])
					return false;
			}
			return true;
		}
		return false;
	}

	template<class T>
	inline bool Array<T>::operator!=(const Array& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	template<class T>
	inline size_t Array<T>::size() const noexcept
	{
		return length_;
	}

	template<class T>
	inline bool Array<T>::empty() const noexcept
	{
		return length_ == 0;
	}

	template<class T>
	inline void Array<T>::resize(size_t newSize)
	{
		Length(newSize);
	}

	template<class T>
	inline void Array<T>::clear()
	{
		delete[] storage_;
		storage_ = nullptr;
		length_ = 0;
	}
	template<class T>
	typename Array<T>::iterator Array<T>::begin() noexcept
	{
		return storage_;
	}
	template<class T>
	typename Array<T>::const_iterator Array<T>::cbegin() const noexcept
	{
		return storage_;
	}

	template<class T>
	typename Array<T>::iterator Array<T>::end() noexcept
	{
		return storage_ + length_;
	}

	template<class T>
	typename Array<T>::const_iterator Array<T>::cend() const noexcept
	{
		return storage_ + length_;
	}

	template<class T>
	inline void Array<T>::Length(const size_t& length)
	{
		return nullptr;
	}
	template<class T>
	inline T* Array<T>::AllocateArray(const size_t& length)
	{
		return nullptr;
	}
}

#endif
