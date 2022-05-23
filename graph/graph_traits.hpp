#ifndef GRAPH_TRAITS_HPP
#define GRAPH_TRAITS_HPP

#include <unordered_map>
#include <unordered_set>

#include "edge.hpp"

namespace std
{
template <typename T>
struct hash<reference_wrapper<T>>
{
	auto operator()(reference_wrapper<T> ref) const
	{
		return hash<std::decay_t<T>>{}(ref.get());
	}
};

template <typename T>
struct equal_to<reference_wrapper<T>>
{
	auto operator()(reference_wrapper<T> lhs, reference_wrapper<T> rhs) const
	{
		return lhs.get() == rhs.get();
	}
};
} // namespace std

namespace gpl
{
struct directed;
struct undirected;

template <typename>
struct is_directed;

template <>
struct is_directed<directed> : public std::true_type
{
};

template <>
struct is_directed<undirected> : public std::false_type
{
};

template <typename T>
constexpr auto is_directed_v = is_directed<T>::value;

struct weighed;
struct unweighed;

template <typename>
struct is_weighed;

template <>
struct is_weighed<weighed> : public std::true_type
{
};

template <>
struct is_weighed<unweighed> : public std::false_type
{
};

template <typename T>
constexpr auto is_weighed_v = is_weighed<T>::value;

template <typename, typename, typename>
struct graph_traits;

template <typename T, typename V>
struct graph_traits<weighed, T, V>
{
	typedef weighed_edge<T, V> edge;
	typedef std::unordered_map<T, std::unordered_map<std::reference_wrapper<const T>, V>> storage;
};

template <typename T, typename V>
struct graph_traits<unweighed, T, V>
{
	typedef base_edge<T> edge;
	typedef std::unordered_map<T, std::unordered_set<std::reference_wrapper<const T>>> storage;
};
} // namespace gpl

#endif // GRAPH_TRAITS_HPP
