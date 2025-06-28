#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class HeapSort final : public ISort<C>
{
public:
	~HeapSort() override = default;
	size_t Sort(C container, const size_t& size) override;
	const char* SortName() override;

private:
	void Heapify(C& container, int size, int root);
};

template <class C>
size_t HeapSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
const char* HeapSort<C>::SortName()
{
	return "Heap Sort";
}

template <class C>
void HeapSort<C>::Heapify(C& container, int size, int root)
{
	
}
#endif
