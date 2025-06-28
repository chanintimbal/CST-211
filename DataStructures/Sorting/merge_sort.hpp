#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class MergeSort final : public ISort<C>
{
public:
	~MergeSort() override = default;
	size_t Sort(C container, const size_t& size) override;	
	const char* SortName() override;

private:
	void Merge(C container, const size_t left, const size_t mid, const size_t right);
	void Sort(C container, const size_t& i, const size_t& j);
};

template <class C>
size_t MergeSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
void MergeSort<C>::Sort(C container, const size_t& i, const size_t& j)
{
	
}

template <class C>
void MergeSort<C>::Merge(C container, const size_t /*left*/i, const size_t mid, const size_t /*right*/j)
{	
	
}

template <class C>
const char* MergeSort<C>::SortName()
{
	return "Merge Sort";
}
#endif
