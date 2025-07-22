#ifndef PAIR_NODE_HPP
#define PAIR_NODE_HPP

#include "node.hpp"

namespace data_structures
{
	template <class K, class V>
	class PairNode : public Node<V>
	{
	public:
		PairNode(const K& key, const V& value);

		PairNode(const PairNode& copy) = default;
		PairNode(PairNode&& copy) noexcept = default;

		~PairNode() override = default;

		PairNode& operator=(const PairNode& rhs) = default;
		PairNode& operator=(PairNode&& rhs) noexcept = default;

		K& Key() noexcept;
		const K& Key() const noexcept;

		void Key(const K& key);

	protected:
		PairNode() = default;
		K key_{};
	};
}
#endif