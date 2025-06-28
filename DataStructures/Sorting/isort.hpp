#ifndef ISORT_HPP
#define ISORT_HPP

template <class C>
class ISort
{
public:
	virtual ~ISort() = default;
	virtual size_t Sort(C container, const size_t& size) = 0;
	virtual const char* SortName() = 0;	
};
#endif
