#ifndef BRUTE_FORCE_BUBBLE_SORT_HPP
#define BRUTE_FORCE_BUBBLE_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class BruteForceBubbleSort final : public ISort<C>
{
public:
	~BruteForceBubbleSort() override = default;
	size_t Sort(C container, const size_t& size) override;
	const char* SortName() override;	
};

template <class C>
size_t BruteForceBubbleSort<C>::Sort(C container, const size_t& size) 
{
	const auto start_time = GetTickCount();
	//Body of sorting code
	

	return GetTickCount() - start_time;
}

template <class C>
const char* BruteForceBubbleSort<C>::SortName()
{
	return "BF Bubble Sort";
}
#endif
