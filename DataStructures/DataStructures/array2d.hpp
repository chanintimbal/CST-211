#ifndef array_2d_HPP
#define array_2d_HPP

#include "array.hpp"
#include "iarray2d.hpp"

namespace data_structures
{
	template <typename T>
	class Array2D final : public IArray2D<T>
	{
	public:
		Array2D() = default;
		~Array2D() override = default;

		explicit Array2D(size_t rows, size_t columns);

		Array2D(const Array2D& copy);
		Array2D& operator=(const Array2D& copy);
		Array2D(Array2D&& copy) noexcept;
		Array2D& operator=(Array2D&& copy) noexcept;

		T Select(size_t row, size_t column) const override;
		T& Select(size_t row, size_t column) override;

		Row<T> operator[](size_t row_index) const override;
		Row<T> operator[](size_t row_index) override;

		explicit operator bool() const noexcept override;

		size_t Rows() const noexcept override;
		size_t Columns() const noexcept override;

		void Rows(const size_t& new_rows) override;
		void Columns(const size_t& new_columns) override;

		bool operator==(const Array2D& rhs) const noexcept;
		bool operator!=(const Array2D& rhs) const noexcept;

	private:
		Array<T> storage_;
		size_t rows_{ 0 };
		size_t columns_{ 0 };

		static void CheckBounds(size_t row, size_t col, size_t rows, size_t cols);
	};
}
#endif
