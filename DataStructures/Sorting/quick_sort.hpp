#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class QuickSort final : public ISort<C>
{
public:
	~QuickSort() override = default;
	size_t Sort(C container, const size_t& size) override;	
	const char* SortName() override;

private:
	void Sort(C& container, int left, int right);
	int Partition(C& container,int left, int right);
};

template <class C>
size_t QuickSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
void QuickSort<C>::Sort(C& container, const int left, const int right)
{
	
}

template <class C>
int QuickSort<C>::Partition(C& container,int left,int right)
{
	return 0;
}

template <class C>
const char* QuickSort<C>::SortName()
{
	return "Quick Sort";
}
#endif