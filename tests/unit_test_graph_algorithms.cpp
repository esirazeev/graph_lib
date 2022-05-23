#include <gtest/gtest.h>

#include "custom_vertex.hpp"
#include "graph/graph.hpp"
#include "graph/graph_algorithms.hpp"

TEST(graph_algorithms_test, dfs_directed_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};
	constexpr custom_vertex v4{4};
	constexpr custom_vertex v5{5};

	gpl::graph<gpl::directed, gpl::unweighed, custom_vertex> graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v4});
	graph.insert_edge({v4, v5});
	graph.insert_edge({v5, v1});

	const std::vector<custom_vertex> expected{v1, v2, v4, v5, v3};
	std::vector<custom_vertex> actual{};

	gpl::dfs(graph, v1, [&](const custom_vertex& vertex) { actual.push_back(vertex); });

	ASSERT_EQ(expected, actual);
}

TEST(graph_algorithms_test, dfs_undirected_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};
	constexpr custom_vertex v4{4};
	constexpr custom_vertex v5{5};

	gpl::graph<gpl::undirected, gpl::unweighed, custom_vertex> graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v4});
	graph.insert_edge({v4, v5});
	graph.insert_edge({v5, v1});

	const std::vector<custom_vertex> expected{v1, v2, v4, v3, v5};
	std::vector<custom_vertex> actual{};

	gpl::dfs(graph, v1, [&](const custom_vertex& vertex) { actual.push_back(vertex); });

	ASSERT_EQ(expected, actual);
}

TEST(graph_algorithms_test, bfs_directed_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};
	constexpr custom_vertex v4{4};
	constexpr custom_vertex v5{5};

	gpl::graph<gpl::directed, gpl::unweighed, custom_vertex> graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v4});
	graph.insert_edge({v4, v5});
	graph.insert_edge({v5, v1});

	const std::vector<custom_vertex> expected{v1, v3, v2, v4, v5};
	std::vector<custom_vertex> actual{};

	gpl::bfs(graph, v1, [&](const custom_vertex& vertex) { actual.push_back(vertex); });

	ASSERT_EQ(expected, actual);
}

TEST(graph_algorithms_test, bfs_undirected_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};
	constexpr custom_vertex v4{4};
	constexpr custom_vertex v5{5};

	gpl::graph<gpl::undirected, gpl::unweighed, custom_vertex> graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v4});
	graph.insert_edge({v4, v5});
	graph.insert_edge({v5, v1});

	const std::vector<custom_vertex> expected{v1, v5, v3, v2, v4};
	std::vector<custom_vertex> actual{};

	gpl::bfs(graph, v1, [&](const custom_vertex& vertex) { actual.push_back(vertex); });

	ASSERT_EQ(expected, actual);
}
