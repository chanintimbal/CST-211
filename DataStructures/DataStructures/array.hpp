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

	}

	template<class T>
	inline Array<T>::Array(const T* storage, const size_t& length)
	{
		T* storage = nullptr;
		try
		{
			storage = new T[length]{};
		}
		catch
		{
			delete[] stroage;
			storage = nullptr;
			throw AdtException(ex.what());
		}

		storage_ = storage;

		for (auto i = 0ull; i < length; ++i)
		{
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
		// TODO: insert return statement here
	}
	template<class T>
	inline Array<T>::Array(Array&& copy) noexcept
	{
	}
	template<class T>
	inline Array& Array<T>::operator=(Array&& rhs) noexcept
	{
		// TODO: insert return statement here
	}
	template<class T>
	inline T& Array<T>::operator[](const size_t& index)
	{
		// TODO: insert return statement here
	}
	template<class T>
	inline const T& Array<T>::operator[](const size_t& index) const
	{
		// TODO: insert return statement here
	}
	template<class T>
	inline Array<T>::operator bool() const noexcept
	{
	}
	template<class T>
	inline bool Array<T>::operator==(const Array& rhs) const noexcept
	{
		return false;
	}
	template<class T>
	inline bool Array<T>::operator!=(const Array& rhs) const noexcept
	{
		return false;
	}
	template<class T>
	inline size_t Array<T>::size() const noexcept
	{
		return size_t();
	}
	template<class T>
	inline bool Array<T>::empty() const noexcept
	{
		return false;
	}
	template<class T>
	inline void Array<T>::resize(size_t newSize)
	{
	}
	template<class T>
	inline void Array<T>::clear()
	{
	}
	template<class T>
	inline iterator Array<T>::begin() noexcept
	{
		return iterator();
	}
	template<class T>
	inline const_iterator Array<T>::begin() const noexcept
	{
		return const_iterator();
	}
	template<class T>
	inline const_iterator Array<T>::cbegin() const noexcept
	{
		return const_iterator();
	}
	template<class T>
	inline iterator Array<T>::end() noexcept
	{
		return iterator();
	}
	template<class T>
	inline const_iterator Array<T>::end() const noexcept
	{
		return const_iterator();
	}
	template<class T>
	inline const_iterator Array<T>::cend() const noexcept
	{
		return const_iterator();
	}
	template<class T>
	inline void Array<T>::Length(const size_t& length)
	{
	}
	template<class T>
	inline T* Array<T>::AllocateArray(const size_t& length)
	{
		T* storage = nullptr;
		try
		{
			storage = new T[length]{};
		}
		catch
		{
			delete[] stroage;
			storage = nullptr;
			throw AdtException(ex.what());
		}

		return storage;
	}
}
#endif
