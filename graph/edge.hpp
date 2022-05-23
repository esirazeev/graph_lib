#ifndef EDGE_HPP
#define EDGE_HPP

namespace gpl
{
template <typename T>
struct base_edge
{
	const T& from;
	const T& to;
};

template <typename T, typename V>
struct weighed_edge : public base_edge<T>
{
	V weight;
};
} // namespace gpl

#endif // EDGE_HPP
