#ifndef BS_POINT_HPP
#define BS_POINT_HPP

namespace bs
{
struct Point
{
	int x, y;

	[[nodiscard]] constexpr auto is_valid() const noexcept
	{
		return x >= 0 && x < 10 && y >= 0 && y < 10;
	}
};
} // namespace bs

#endif // BS_POINT_HPP
