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
        using typename IAdtIterator<T>::iterator_category;
        using typename IAdtIterator<T>::value_type;
        using typename IAdtIterator<T>::reference;
        using typename IAdtIterator<T>::pointer;
        using typename IAdtIterator<T>::difference_type;
        using typename IAdtIterator<T>::const_reference;
        using typename IAdtIterator<T>::const_pointer;

        ListIterator() noexcept = default;
        explicit ListIterator(ListNode<T>* start, ListNode<T>* tail, bool forward = true) noexcept
            : current_(start), tail_(tail), forward_(forward) {}

        ListIterator(const ListIterator&) noexcept = default;
        ListIterator(ListIterator&&) noexcept = default;
        ListIterator& operator=(const ListIterator&) noexcept = default;
        ListIterator& operator=(ListIterator&&) noexcept = default;
        ~ListIterator() override = default;

        explicit operator bool() const noexcept { return current_ != nullptr; }
        bool AtEnd() const noexcept { return current_ == nullptr; }

        reference Value() { Check(); return current_->Value(); }
        const_reference Value() const { Check(); return current_->Value(); }

        reference operator*() override { return Value(); }
        const_reference operator*() const override { return Value(); }

        pointer operator->() override { Check(); return &(current_->Value()); }
        const_pointer operator->() const override { Check(); return &(current_->Value()); }

        ListIterator& operator++() override
        {
            Check();
            current_ = forward_ ? current_->Next() : current_->Prev();
            return *this;
        }

        ListIterator operator++(int)
        {
            ListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ListIterator& operator--() override
        {
            if (!current_)
                current_ = tail_;
            else
                current_ = forward_ ? current_->Prev() : current_->Next();
            return *this;
        }

        ListIterator operator--(int)
        {
            ListIterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const IAdtIterator<T>& o) const override
        {
            auto* other = dynamic_cast<const ListIterator*>(&o);
            return other && current_ == other->current_;
        }

        bool operator!=(const IAdtIterator<T>& o) const override
        {
            return !(*this == o);
        }

        void Reset() noexcept
        {
            current_ = forward_ ? tail_ : nullptr;
            while (current_ && (forward_ ? current_->Prev() : current_->Next()))
            {
                current_ = forward_ ? current_->Prev() : current_->Next();
            }
        }

    private:
        ListNode<T>* current_{ nullptr };
        ListNode<T>* tail_{ nullptr };
        bool forward_{ true };

        void Check() const
        {
            if (!current_)
                throw AdtException("Iterator out of bounds.");
        }
    };
}

#endif
