#ifndef ROW_H
#define ROW_H

namespace data_structures
{
	template <class T>
	class IArray2D;

	template <class T>
	class Row final
	{
	public:
		Row(const IArray2D<T>& arr, size_t row_index);
		T operator[](size_t column) const;
		T& operator[](size_t column);

	private:
		const IArray2D<T>& arr_;
		size_t row_;
	};

	template <class T>
	Row<T>::Row(const IArray2D<T>& arr, size_t row_index)
		:arr_(arr), row_(row_index) {}

	template <class T>
	T Row<T>::operator[](size_t column) const
	{
		return arr_.Select(row_, column);
	}

	template <class T>
	T& Row<T>::operator[](size_t column)
	{
		return const_cast<IArray2D<T>&>(arr_).Select(row_, column);
	}

}
#endif 