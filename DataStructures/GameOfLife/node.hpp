#ifndef NODE_HPP
#define NODE_HPP

#include <algorithm>

namespace data_structures
{
	template <class T>
	class Node
	{
	public:
		explicit Node() = delete;

		explicit Node(const T& copy); //copy-in
		explicit Node(T&& node); //move-in

		Node(const Node&);
		Node& operator=(const Node&);

		Node(Node&&) noexcept;
		Node& operator=(Node&&) noexcept;

		virtual ~Node() = default;

		T& Value() noexcept;
		const T& Value() const noexcept;

		void Value(const T& data);
		void Value(T&& data);

		bool operator==(const Node& rhs) const noexcept;
		bool operator!=(const Node& rhs) const noexcept;

	private:
		T value_{};
	};


}
#endif
