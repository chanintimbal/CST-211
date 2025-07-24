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
	template <class T>
	Node<T>::Node(const T& copy)
		: value_{ copy }
	{
	}

	// Move-in constructor
	template <class T>
	Node<T>::Node(T&& node)
		: value_{ std::move(node) }
	{
	}

	// Copy constructor
	template <class T>
	Node<T>::Node(const Node& other)
		: value_{ other.value_ }
	{
	}

	// Copy assignment
	template <class T>
	Node<T>& Node<T>::operator=(const Node& rhs)
	{
		if (this != &rhs)
		{
			value_ = rhs.value_;
		}
		return *this;
	}
	template <class T>
	Node<T>::Node(Node&& other) noexcept
		: value_{ std::move(other.value_) }
	{
	}

	template <class T>
	Node<T>& Node<T>::operator=(Node&& rhs) noexcept
	{
		if (this != &rhs)
		{
			value_ = std::move(rhs.value_);
		}
		return *this;
	}

	template <class T>
	T& Node<T>::Value() noexcept
	{
		return value_;
	}

	template <class T>
	const T& Node<T>::Value() const noexcept
	{
		return value_;
	}

	template <class T>
	void Node<T>::Value(const T& data)
	{
		value_ = data;
	}

	template <class T>
	void Node<T>::Value(T&& data)
	{
		value_ = std::move(data);
	}

	template <class T>
	bool Node<T>::operator==(const Node& rhs) const noexcept
	{
		return value_ == rhs.value_;
	}

	template <class T>
	bool Node<T>::operator!=(const Node& rhs) const noexcept
	{
		return !(*this == rhs);
	}
}

#endif