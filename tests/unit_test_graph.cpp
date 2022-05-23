#include <gtest/gtest.h>

#include "custom_vertex.hpp"
#include "graph/graph.hpp"

TEST(graph_test, default_construct)
{
	const gpl::graph<gpl::directed, gpl::weighed, custom_vertex> weighed_directed_graph;
	ASSERT_TRUE(weighed_directed_graph.is_directed());
	ASSERT_TRUE(weighed_directed_graph.is_weighed());

	const gpl::graph<gpl::undirected, gpl::weighed, custom_vertex> weighed_undirected_graph;
	ASSERT_FALSE(weighed_undirected_graph.is_directed());
	ASSERT_TRUE(weighed_undirected_graph.is_weighed());

	const gpl::graph<gpl::directed, gpl::unweighed, custom_vertex> unweighed_directed_graph;
	ASSERT_TRUE(unweighed_directed_graph.is_directed());
	ASSERT_FALSE(unweighed_directed_graph.is_weighed());

	const gpl::graph<gpl::undirected, gpl::unweighed, custom_vertex> unweighed_undirected_graph;
	ASSERT_FALSE(unweighed_undirected_graph.is_directed());
	ASSERT_FALSE(unweighed_undirected_graph.is_weighed());
}

TEST(graph_test, insert_edge_undirected_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};
	constexpr custom_vertex v4{4};

	using unweighed_graph_t = gpl::graph<gpl::undirected, gpl::unweighed, custom_vertex>;

	unweighed_graph_t graph_1;
	graph_1.insert_edge({v1, v2});
	graph_1.insert_edge({v1, v3});
	graph_1.insert_edge({v1, v2});

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v1{
		std::reference_wrapper<const custom_vertex>{v2}, std::reference_wrapper<const custom_vertex>{v3}};

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v2_v3{
		std::reference_wrapper<const custom_vertex>{v1}};

	ASSERT_EQ(unweighed_adjacency_table_v1, *graph_1.get_adjacency_table(v1));
	ASSERT_EQ(unweighed_adjacency_table_v2_v3, *graph_1.get_adjacency_table(v2));
	ASSERT_EQ(unweighed_adjacency_table_v2_v3, *graph_1.get_adjacency_table(v3));
	ASSERT_FALSE(graph_1.get_adjacency_table(v4));

	constexpr auto weight_v1_v2{1};
	constexpr auto weight_v1_v3{2};

	using weighed_graph_t = gpl::graph<gpl::undirected, gpl::weighed, custom_vertex>;

	weighed_graph_t graph_2;
	graph_2.insert_edge({v1, v2, weight_v1_v3});
	graph_2.insert_edge({v1, v3, weight_v1_v3});
	graph_2.insert_edge({v1, v2, weight_v1_v2});

	const weighed_graph_t::adjacency_table_t weighed_adjacency_table_v1{
		{std::reference_wrapper<const custom_vertex>{v2}, weight_v1_v2},
		{std::reference_wrapper<const custom_vertex>{v3}, weight_v1_v3}};

	const weighed_graph_t::adjacency_table_t weighed_adjacency_table_v2{
		{std::reference_wrapper<const custom_vertex>{v1}, weight_v1_v2}};
	const weighed_graph_t::adjacency_table_t weighed_adjacency_table_v3{
		{std::reference_wrapper<const custom_vertex>{v1}, weight_v1_v3}};

	ASSERT_EQ(weighed_adjacency_table_v1, *graph_2.get_adjacency_table(v1));
	ASSERT_EQ(weighed_adjacency_table_v2, *graph_2.get_adjacency_table(v2));
	ASSERT_EQ(weighed_adjacency_table_v3, *graph_2.get_adjacency_table(v3));
	ASSERT_FALSE(graph_2.get_adjacency_table(v4));
}

TEST(graph_test, insert_edge_directed_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};
	constexpr custom_vertex v4{4};

	using unweighed_graph_t = gpl::graph<gpl::directed, gpl::unweighed, custom_vertex>;

	unweighed_graph_t graph_1;
	graph_1.insert_edge({v1, v2});
	graph_1.insert_edge({v1, v3});

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v1{
		std::reference_wrapper<const custom_vertex>{v2}, std::reference_wrapper<const custom_vertex>{v3}};

	ASSERT_EQ(unweighed_adjacency_table_v1, *graph_1.get_adjacency_table(v1));
	ASSERT_TRUE(graph_1.get_adjacency_table(v2)->empty());
	ASSERT_TRUE(graph_1.get_adjacency_table(v3)->empty());
	ASSERT_FALSE(graph_1.get_adjacency_table(v4));

	constexpr auto weight_v1_v2{1};
	constexpr auto weight_v1_v3{2};

	using weighed_graph_t = gpl::graph<gpl::directed, gpl::weighed, custom_vertex>;

	weighed_graph_t graph_2;
	graph_2.insert_edge({v1, v3, weight_v1_v3});
	graph_2.insert_edge({v1, v2, weight_v1_v2});

	const weighed_graph_t::adjacency_table_t weighed_adjacency_table_v1{
		{std::reference_wrapper<const custom_vertex>{v2}, weight_v1_v2},
		{std::reference_wrapper<const custom_vertex>{v3}, weight_v1_v3}};

	ASSERT_EQ(weighed_adjacency_table_v1, *graph_2.get_adjacency_table(v1));
	ASSERT_TRUE(graph_2.get_adjacency_table(v2)->empty());
	ASSERT_TRUE(graph_2.get_adjacency_table(v3)->empty());
	ASSERT_FALSE(graph_2.get_adjacency_table(v4));
}

TEST(graph_test, erase_vertex_directed_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};

	using unweighed_graph_t = gpl::graph<gpl::directed, gpl::unweighed, custom_vertex>;

	unweighed_graph_t graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v3});
	graph.erase_vertex(v3);

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v1{
		std::reference_wrapper<const custom_vertex>{v2}};

	ASSERT_EQ(unweighed_adjacency_table_v1, *graph.get_adjacency_table(v1));
	ASSERT_TRUE(graph.get_adjacency_table(v2)->empty());
	ASSERT_FALSE(graph.get_adjacency_table(v3));
}

TEST(graph_test, erase_vertex_undirected_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};

	using unweighed_graph_t = gpl::graph<gpl::undirected, gpl::unweighed, custom_vertex>;

	unweighed_graph_t graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v3});
	graph.erase_vertex(v1);

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v2{
		std::reference_wrapper<const custom_vertex>{v3}};

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v3{
		std::reference_wrapper<const custom_vertex>{v2}};

	ASSERT_EQ(unweighed_adjacency_table_v2, *graph.get_adjacency_table(v2));
	ASSERT_EQ(unweighed_adjacency_table_v3, *graph.get_adjacency_table(v3));
	ASSERT_FALSE(graph.get_adjacency_table(v1));
}

TEST(graph_test, erase_edge_directed_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};

	using unweighed_graph_t = gpl::graph<gpl::directed, gpl::unweighed, custom_vertex>;

	unweighed_graph_t graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v3});
	graph.insert_edge({v3, v1});
	graph.erase_edge({v1, v3});

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v1{
		std::reference_wrapper<const custom_vertex>{v2}};

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v2{
		std::reference_wrapper<const custom_vertex>{v3}};

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v3{
		std::reference_wrapper<const custom_vertex>{v1}};

	ASSERT_EQ(unweighed_adjacency_table_v1, *graph.get_adjacency_table(v1));
	ASSERT_EQ(unweighed_adjacency_table_v2, *graph.get_adjacency_table(v2));
	ASSERT_EQ(unweighed_adjacency_table_v3, *graph.get_adjacency_table(v3));
}

TEST(graph_test, erase_edge_undirected_graph)
{
	constexpr custom_vertex v1{1};
	constexpr custom_vertex v2{2};
	constexpr custom_vertex v3{3};

	using unweighed_graph_t = gpl::graph<gpl::undirected, gpl::unweighed, custom_vertex>;

	unweighed_graph_t graph;
	graph.insert_edge({v1, v2});
	graph.insert_edge({v1, v3});
	graph.insert_edge({v2, v3});
	graph.erase_edge({v2, v3});

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v1{
		std::reference_wrapper<const custom_vertex>{v2}, std::reference_wrapper<const custom_vertex>{v3}};

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v2{
		std::reference_wrapper<const custom_vertex>{v1}};

	const unweighed_graph_t::adjacency_table_t unweighed_adjacency_table_v3{
		std::reference_wrapper<const custom_vertex>{v1}};

	ASSERT_EQ(unweighed_adjacency_table_v1, *graph.get_adjacency_table(v1));
	ASSERT_EQ(unweighed_adjacency_table_v2, *graph.get_adjacency_table(v2));
	ASSERT_EQ(unweighed_adjacency_table_v3, *graph.get_adjacency_table(v3));
}
