#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

#include "node.hpp"

namespace data_structures
{
	template <class T>
	class ListNode final : public Node<T>
	{
	public:
		ListNode() = delete;
		explicit ListNode(const T& data, ListNode* next = nullptr, ListNode* previous = nullptr);

		ListNode(const ListNode& copy);
		ListNode& operator=(const ListNode& rhs);

		ListNode(ListNode&& copy) noexcept;
		ListNode& operator=(ListNode&& rhs) noexcept;

		ListNode* Next() noexcept;
		ListNode* Next() const noexcept;
		ListNode* Prev() noexcept;
		ListNode* Prev() const noexcept;

		void Next(ListNode* next) noexcept;
		void Prev(ListNode* previous) noexcept;

		bool operator==(const ListNode& rhs) const noexcept;
		bool operator!=(const ListNode& rhs) const noexcept;

		~ListNode() override = default;

	private:
		ListNode* next_{ nullptr };
		ListNode* prev_{ nullptr };
	};

}
#endif
