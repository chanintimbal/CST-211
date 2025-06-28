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
}

#endif
