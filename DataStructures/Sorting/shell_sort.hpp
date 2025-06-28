#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include <Windows.h>
#include "isort.hpp"

template <class C>
class ShellSort final : public ISort<C>
{
public:
	~ShellSort() override = default;
	size_t Sort(C container, const size_t& size) override;
	const char* SortName() override;
};

template <class C>
size_t ShellSort<C>::Sort(C container, const size_t& size)
{
	const auto start_time = GetTickCount();
	//Body of sorting code

	return GetTickCount() - start_time;
}

template <class C>
const char* ShellSort<C>::SortName()
{
	return "Shell Sort";
}
#endif
