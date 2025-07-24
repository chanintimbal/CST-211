#ifndef IADT_ITERATOR_HPP
#define IADT_ITERATOR_HPP
#include <iterator>

namespace data_structures
{
    template<class T>
    class IAdtIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using const_reference = const T&;
        using const_pointer = const T*;

        /* 1 - virtual dtor must *not* be pure,          */
        /*     otherwise every derived iterator is still */
        /*     abstract even if it overrides everything. */
        virtual ~IAdtIterator() = default;

        virtual reference operator*() = 0;
        virtual const_reference operator*() const = 0;

        virtual pointer operator->() = 0;
        virtual const_pointer operator->() const = 0;

        virtual IAdtIterator& operator++() = 0;
        virtual IAdtIterator& operator--() = 0;

        virtual bool operator==(const IAdtIterator& rhs) const = 0;
        virtual bool operator!=(const IAdtIterator& rhs) const = 0;
    };
}
#endif