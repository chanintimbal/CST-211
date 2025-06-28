#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class SelectionSort final : public ISort<C>
{
public:
	~SelectionSort() override = default;
	size_t Sort(C container, const size_t& size) override;	
	const char* SortName() override;
};

template <class C>
size_t SelectionSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
const char* SelectionSort<C>::SortName()
{
	return "Selection Sort";
}
#endif
