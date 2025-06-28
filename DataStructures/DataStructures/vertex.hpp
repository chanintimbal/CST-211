#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "arc.hpp"
#include "linked_list.hpp"
#include "adt_exception.hpp"

namespace data_structures
{
	template <class V, class E>
	class Arc;

	template <class V, class E>
	class Vertex final
	{
	public:
		using iterator = ListIterator<Arc<V, E>>;
		using const_iterator = ListIterator<Arc<V, E>>;

		Vertex() = delete;
		explicit Vertex(V data);
		~Vertex() = default;

		Vertex(const Vertex<V, E>& other);
		Vertex<V, E>& operator=(const Vertex<V, E>& rhs);

		Vertex(Vertex<V, E>&& other) noexcept;
		Vertex<V, E>& operator=(Vertex<V, E>&& rhs) noexcept;

		V& Data() noexcept;
		const V& Data() const noexcept;

		void AddArc(Arc<V, E> arc);

		LinkedList<Arc<V, E>>& Arcs();
		const LinkedList<Arc<V, E>>& Arcs() const;

		void RemoveArc(const E& arc_data);

		int OutDegree() const noexcept;

		void IsProcessed(const bool& processed) noexcept;
		bool IsProcessed() const noexcept;

		bool operator==(const Vertex& rhs) const noexcept;
		bool operator!=(const Vertex& rhs) const noexcept;

		/* ----------------------------------------------------------------------- */
		/*  Forward iteration                                                     */
		/* ----------------------------------------------------------------------- */
		iterator       begin();
		iterator       end();

		const_iterator begin() const;
		const_iterator end()   const;

		const_iterator cbegin() const;
		const_iterator cend()   const;

		/* ----------------------------------------------------------------------- */
		/*  Reverse iteration (optional)                                           */
		/* ----------------------------------------------------------------------- */
		iterator       rbegin();
		iterator       rend();

		const_iterator rbegin() const;
		const_iterator rend()   const;

		const_iterator crbegin() const;
		const_iterator crend()   const;

	private:
		V data_{};
		bool processed_{ false };
		LinkedList<Arc<V, E>> arcs_{};
	};

	

}
#endif
