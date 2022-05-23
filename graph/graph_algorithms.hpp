#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <functional>
#include <queue>
#include <stack>

#include "graph.hpp"

namespace gpl
{
template <typename Direction, typename WeightCategory, VertexConcept Vertex>
using callback_t = std::function<void(const typename graph<Direction, WeightCategory, Vertex>::vertex_t&)>;

template <bool is_weighed, typename T>
constexpr auto get_vertex_ref(const T& item)
{
	if constexpr (is_weighed)
	{
		return item.first;
	}
	else
	{
		return item;
	}
}

template <typename Direction, typename WeightCategory, VertexConcept Vertex>
void dfs(
	const graph<Direction, WeightCategory, Vertex>& graph, const Vertex& vertex,
	callback_t<Direction, WeightCategory, Vertex> callback)
{
	std::unordered_set<std::reference_wrapper<const Vertex>> visited;
	visited.insert({vertex});

	std::stack<std::reference_wrapper<const Vertex>> stack;
	stack.push({vertex});

	while (!stack.empty())
	{
		auto cur_vertex_ref{stack.top()};
		stack.pop();

		auto adjacency_table{graph.get_adjacency_table(cur_vertex_ref.get())};

		if (!adjacency_table)
		{
			return;
		}

		callback(cur_vertex_ref.get());

		for (const auto& adjacency_vertex : *adjacency_table)
		{
			const auto vertex_ref{get_vertex_ref<gpl::is_weighed_v<WeightCategory>>(adjacency_vertex)};

			if (visited.insert(vertex_ref).second)
			{
				stack.push(vertex_ref);
			}
		}
	}
}

template <typename Direction, typename WeightCategory, VertexConcept Vertex>
void bfs(
	const graph<Direction, WeightCategory, Vertex>& graph, const Vertex& vertex,
	callback_t<Direction, WeightCategory, Vertex> callback)
{
	std::unordered_set<std::reference_wrapper<const Vertex>> visited;
	visited.insert({vertex});

	std::queue<std::reference_wrapper<const Vertex>> queue;
	queue.push({vertex});

	while (!queue.empty())
	{
		auto cur_vertex_ref{queue.front()};
		queue.pop();

		auto adjacency_table{graph.get_adjacency_table(cur_vertex_ref.get())};

		if (!adjacency_table)
		{
			return;
		}

		callback(cur_vertex_ref.get());

		for (const auto& adjacency_vertex : *adjacency_table)
		{
			const auto vertex_ref{get_vertex_ref<gpl::is_weighed_v<WeightCategory>>(adjacency_vertex)};

			if (visited.insert(vertex_ref).second)
			{
				queue.push(vertex_ref);
			}
		}
	}
}
} // namespace gpl

#endif // GRAPH_ALGORITHMS_HPP
