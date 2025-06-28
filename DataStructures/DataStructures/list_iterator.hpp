#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include "adt_exception.hpp"
#include "i_adt_iterator.hpp"
#include "list_node.hpp"

namespace data_structures
{
    template<class T>
    class ListIterator : public IAdtIterator<T>
    {
    public:
        //iterator traits so STL algorithms recognise us
        using typename IAdtIterator<T>::iterator_category;
        using typename IAdtIterator<T>::value_type;
        using typename IAdtIterator<T>::reference;
        using typename IAdtIterator<T>::pointer;
        using typename IAdtIterator<T>::difference_type;
        using typename IAdtIterator<T>::const_reference;
        using typename IAdtIterator<T>::const_pointer;

        //ctors / assignment (all defaultable)
        ListIterator() noexcept = default;
        explicit ListIterator(ListNode<T>* start, ListNode<T>* tail, bool forward = true) noexcept;
        ListIterator(const ListIterator&) noexcept = default;
        ListIterator(ListIterator&&) noexcept = default;
        ListIterator& operator=(const ListIterator&) noexcept = default;
        ListIterator& operator=(ListIterator&&) noexcept = default;
        ~ListIterator() override = default;

        //convenience
        explicit operator bool() const noexcept;
        bool AtEnd() const noexcept;

        //IIterator interface*/
        reference Value();
        const_reference Value() const;

        //STL-style dereference
        reference operator*() override;
        const_reference operator*() const override;

        pointer operator->() override;
        const_pointer operator->() const override;

        //Bi-Directional Navigation
        ListIterator& operator++() override;          // prefix ++
        ListIterator operator++(int);       // postfix ++
        ListIterator& operator--() override;          // prefix --
        ListIterator operator--(int);       // postfix --

        //Compare
        bool operator==(const IAdtIterator<T>& o) const override;
        bool operator!=(const IAdtIterator<T>& o) const override;

        //Resetting to list head (walk prev links)
        void Reset() noexcept;

    private:
        ListNode<T>* current_{ nullptr }; // nullptr == end()
        ListNode<T>* tail_{ nullptr }; // nullptr == end()
        bool forward_{ true };      // true: begin()/end(), false: rbegin()/rend()
        void Check() const;         // throw if AtEnd()
    };


}

#endif 