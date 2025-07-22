#ifndef array_2d_HPP
#define array_2d_HPP

#include "array.hpp"
#include "iarray2d.hpp"

namespace data_structures
{
	template <typename T>
	class Array2D : public IArray2D<T>
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

	template <typename T>
	Array2D<T>::Array2D(size_t rows, size_t columns)
	: storage_(rows*columns), rows_(rows), columns_(columns) {}

	template <typename T>
	Array2D<T>::Array2D(const Array2D& copy)
		: storage_(std::move(copy.storage_)), rows_(copy.rows_), columns_(copy.columns_) {}

	template <typename T>
	Array2D<T>& Array2D<T>::operator=(const Array2D& copy)
	{
		if (this != &copy)
		{
			rows_ = copy.rows_;
			columns_ = copy.columns_;
			storage_ = copy.storage_;
		}
		return *this;
	}

	template <typename T>
	Array2D<T>::Array2D(Array2D&& copy) noexcept
		: storage_(std::move(copy.storage_)), rows_(copy.rows_), columns_(copy.columns_)
	{
		copy.rows_ = copy.columns_ = 0;
	}

	template <typename T>
	Array2D<T>& Array2D<T>::operator=(Array2D&& copy) noexcept
	{
		if (this!= &copy)
		{
			rows_ = copy.rows_;
			columns_ = copy.columns_;
			storage_ = std::move(copy.storage_);
			copy.rows_ = copy.columns_ = 0;
		}
		return *this;
	}

	template <typename T>
	T Array2D<T>::Select(size_t row, size_t column) const
	{
		CheckBounds(row, column, rows_, columns_);
		return storage_[row * columns_ + column];
	}

	template <typename T>
	T& Array2D<T>::Select(size_t row, size_t column)
	{
		CheckBounds(row, column, rows_, columns_);
		return storage_[row * columns_ + column];
	}

	template <typename T>
	Row<T> Array2D<T>::operator[](size_t row_index) const
	{
		if (row_index >= rows_) throw AdtException("Row index out of bounds.");
		return Row<T>(*this, row_index);
	}

	template <typename T>
	Row<T> Array2D<T>::operator[](size_t row_index)
	{
		if (row_index >= rows_) throw AdtException("Row index out of bounds.");
		return Row<T>(*this, row_index);
	}

	template <typename T>
	Array2D<T>::operator bool() const noexcept
	{
		if (rows_ == 0 || columns_ == 0) return false;
		return static_cast<bool>(storage_);
	}

	template <typename T>
	size_t Array2D<T>::Rows() const noexcept
	{
		return rows_;
	}

	template <typename T>
	size_t Array2D<T>::Columns() const noexcept
	{
		return columns_;
	}

	template <typename T>
	void Array2D<T>::Rows(const size_t& new_rows)
	{
		if (new_rows == 0)
		{
			rows_ = 0;
			storage_.resize(0);
			return;
		}

		// Reduction and grow
		// copy the array to temp array, overwrite the original with copy

		Array<T> temp_array(new_rows * columns_);

		size_t some_t = std::min(rows_, new_rows) * columns_;

		for (size_t i = 0; i < some_t; ++i)
		{
			temp_array[i] = storage_[i];
		}

		storage_ = std::move(temp_array);
		rows_ = new_rows;
	}

	template <typename T>
	void Array2D<T>::Columns(const size_t& new_columns)
	{
		if (new_columns == 0)
		{
			columns_ = 0;
			storage_.resize(0);
			return;
		}

		Array<T> temp_array(rows_ * new_columns);

		size_t some_t = std::min(columns_, new_columns);

		for (size_t row = 0; row < rows_; ++row)
		{
			for (size_t col = 0; col < some_t; ++col)
			{
				temp_array[row * new_columns + col] = storage_[row * columns_ + col];
			}
		}

		storage_ = std::move(temp_array);
		columns_ = new_columns;
	}

	template <typename T>
	bool Array2D<T>::operator==(const Array2D& rhs) const noexcept
	{
		
		if (rows_ != rhs.rows_ || columns_ != rhs.columns_)
			return false;

		// Compare
		for (size_t i = 0; i < rows_ * columns_; ++i)
		{
			if (storage_[i] != rhs.storage_[i])
				return false;
		}

		return true;
	}

	template <typename T>
	bool Array2D<T>::operator!=(const Array2D& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	template <typename T>
	void Array2D<T>::CheckBounds(size_t row, size_t col, size_t rows, size_t cols)
	{
		if (row >= rows || col >= cols)
			throw AdtException("Select() Out of bounds");
	}
}
#endif
