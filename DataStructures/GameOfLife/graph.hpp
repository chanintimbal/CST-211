#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <functional>
#include "vertex.hpp"
#include "adt_exception.hpp"
#include "list_queue.hpp"
#include "list_stack.hpp"

namespace data_structures
{
	template <class V, class E>
	class Graph final
	{
	public:
		using iterator = typename LinkedList<Vertex<V, E>>::iterator;
		using const_iterator = typename LinkedList<Vertex<V, E>>::const_iterator;

		Graph() = default;
		~Graph() = default;

		Graph(const Graph& other);
		Graph& operator=(const Graph& rhs);

		Graph(Graph&& other) noexcept;
		Graph& operator=(Graph&& rhs) noexcept;

		void ResetVertices() noexcept;							//Sets 'processed' in Vertex to false.

		void InsertVertex(const V& data);
		void RemoveVertex(const V& data);

		void InsertArc(const V& from, const V& to, const E& data, const int& weight);
		void RemoveArc(const V& from, const V& to, const E& data);

		void DepthFirst(const V& start_data);
		void BreadthFirst(const V& start_data);

		Vertex<V, E>* GetVertex(const V& data);

		LinkedList<Vertex<V, E>>& Vertices();
		const LinkedList<Vertex<V, E>>& Vertices() const;

		bool IsEmpty() const noexcept;

		size_t NumVertices() const noexcept;

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

		void VisitFunction(const std::function<void(const V& data)>& visit);

	private:
		std::function<void(const V& data)> visit_{ nullptr };
		LinkedList<Vertex<V, E>> vertices_{};
	};

}

#endif
