#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_traits.hpp"

namespace gpl
{
template <typename T>
concept VertexConcept = requires(T obj)
{
	requires !std::is_pointer_v<T>;
	requires !std::is_reference_v<T>;
	requires std::equality_comparable<T>;
	{
		std::hash<T>{}(obj)
		} -> std::convertible_to<std::size_t>;
};

template <typename Direction, typename WeightCategory, VertexConcept Vertex>
class graph final
{
public:
	using weigh_t = uint32_t;
	using vertex_t = Vertex;
	using edge_t = graph_traits<WeightCategory, Vertex, weigh_t>::edge;
	using storage_t = graph_traits<WeightCategory, Vertex, weigh_t>::storage;
	using adjacency_table_t = storage_t::mapped_type;

	graph() = default;
	graph(const graph&) = delete;
	graph(graph&&) = default;
	graph& operator=(const graph&) = delete;
	graph& operator=(graph&&) = default;

	[[nodiscard]] constexpr bool is_directed() const noexcept
	{
		return is_directed_v<Direction>;
	};

	[[nodiscard]] constexpr bool is_weighed() const noexcept
	{
		return is_weighed_v<WeightCategory>;
	}

	void insert_edge(const edge_t& edge)
	{
		const auto result_from{storage_.insert({edge.from, {}}).first};
		const auto result_to{storage_.insert({edge.to, {}}).first};

		if constexpr (is_weighed_v<WeightCategory>)
		{
			result_from->second.insert_or_assign({result_to->first}, edge.weight);

			if (!is_directed())
			{
				result_to->second.insert_or_assign({result_from->first}, edge.weight);
			}
		}
		else
		{
			result_from->second.insert({result_to->first});

			if (!is_directed())
			{
				result_to->second.insert({result_from->first});
			}
		}
	}

	void erase_vertex(const vertex_t& vertex)
	{
		const auto result{storage_.find(vertex)};

		if (result == storage_.cend())
		{
			return;
		}

		if (is_directed())
		{
			for (auto& pair : storage_)
			{
				pair.second.erase({result->first});
			}
		}
		else
		{
			for (auto& adjacency_vertex_ref : result->second)
			{
				storage_[adjacency_vertex_ref.get()].erase({result->first});
			}
		}

		storage_.erase(result);
	}

	void erase_edge(const edge_t& edge)
	{
		const auto result_from{storage_.find(edge.from)};
		const auto result_to{storage_.find(edge.to)};

		if (result_from == storage_.cend() || result_to == storage_.cend())
		{
			return;
		}

		result_from->second.erase({result_to->first});

		if (!is_directed())
		{
			result_to->second.erase({result_from->first});
		}
	}

	const adjacency_table_t* get_adjacency_table(const vertex_t& vertex) const
	{
		auto result{storage_.find(vertex)};

		return result != storage_.cend() ? &result->second : nullptr;
	}

private:
	storage_t storage_;
};
} // namespace gpl

#endif // GRAPH_HPP
