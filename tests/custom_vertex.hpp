#ifndef CUSTOM_VERTEX_HPP
#define CUSTOM_VERTEX_HPP

#include <cstdint>
#include <functional>

struct custom_vertex final
{
	constexpr explicit custom_vertex(int32_t value) noexcept : value_(value) {}

	friend bool operator==(const custom_vertex& lhs, const custom_vertex& rhs)
	{
		return lhs.value_ == rhs.value_;
	}

	int32_t value_;
};

namespace std
{
template <>
struct hash<custom_vertex>
{
	auto operator()(const custom_vertex& vertex) const
	{
		return hash<decltype(vertex.value_)>{}(vertex.value_);
	}
};
} // namespace std

#endif // CUSTOM_VERTEX_HPP
