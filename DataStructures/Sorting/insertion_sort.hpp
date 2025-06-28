#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class InsertionSort final : public ISort<C>
{
public:
	~InsertionSort() override = default;	
	size_t Sort(C container, const size_t& size) override;	
	const char* SortName() override;	
};

template <class C>
size_t InsertionSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
const char* InsertionSort<C>::SortName()
{
	return "Insertion Sort";
}
#endif
