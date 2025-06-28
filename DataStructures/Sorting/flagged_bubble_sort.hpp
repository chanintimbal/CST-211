#ifndef FLAGGED_BUBBLE_SORT_HPP
#define FLAGGED_BUBBLE_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class FlaggedBubbleSort final : public ISort<C>
{
public:
	~FlaggedBubbleSort() override = default;
	size_t Sort(C container, const size_t& size) override;	
	const char* SortName() override;	
};

template <class C>
size_t FlaggedBubbleSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
const char* FlaggedBubbleSort<C>::SortName()
{
	return "Flag Bubble Sort";
}
#endif
