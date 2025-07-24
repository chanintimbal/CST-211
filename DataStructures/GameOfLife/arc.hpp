#ifndef ARC_HPP
#define ARC_HPP

namespace data_structures
{
	template <class V, class E>
	class Vertex;

	template <class V, class E>
	class Arc final
	{
	public:
		Arc() = delete;
		Arc(Vertex<V, E>* destination, E data, int weight);
		~Arc() = default;

		Arc(const Arc& copy) = default;
		Arc& operator=(const Arc& rhs) = default;

		Arc(Arc&& copy) noexcept = default;
		Arc& operator=(Arc&& rhs) noexcept = default;

		Vertex<V, E>* Destination() const noexcept;
		void Destination(Vertex<V, E>* destination);

		int Weight() const noexcept;

		E& Data() noexcept;
		const E& Data() const noexcept;

		bool operator==(const Arc& rhs) const noexcept;
		bool operator!=(const Arc& rhs) const noexcept;

	private:
		Vertex<V, E>* destination_{ nullptr };
		E data_{};
		int weight_{ 0 };
	};

	
}

#endif