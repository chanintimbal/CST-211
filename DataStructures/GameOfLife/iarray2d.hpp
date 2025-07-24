#ifndef IARRAY2D
#define IARRAY2D

#include "row.hpp"

namespace data_structures
{
	template <class T>
	class Row;

	template <class T>
	class IArray2D
	{
	public:
		virtual ~IArray2D() = default;
		virtual T Select(size_t row, size_t column) const = 0;
		virtual T& Select(size_t row, size_t column) = 0;
		virtual Row<T> operator[](size_t row) const = 0;
		virtual Row<T> operator[](size_t row) = 0;
		virtual explicit operator bool() const noexcept = 0;
		virtual size_t Rows() const noexcept = 0;
		virtual size_t Columns() const noexcept = 0;
		virtual void Rows(const size_t& rows) = 0;
		virtual void Columns(const size_t& columns) = 0;
	};

}
#endif