#ifndef BS_SHIP_HPP
#define BS_SHIP_HPP

#include <bitset>

#include "display.hpp"
#include "point.hpp"

namespace bs
{
class Ship
{
public:
	constexpr Ship(const Point t_position, const int t_size, const bool t_vertical)
		: m_position(t_position), m_size(t_size),
		  // Initialise the bitset with the "m_size" least significant bits set to one
		  m_cells_alive((1 << m_size) - 1), m_vertical(t_vertical)
	{
	}

	[[nodiscard]] constexpr auto occupies(const Point t_cell) const noexcept
	{
		if (m_vertical)
		{
			return (t_cell.x == m_position.x) &&
				   ((t_cell.y - m_position.y) >= 0 && (t_cell.y - m_position.y) < m_size);
		}
		return (t_cell.y == m_position.y) &&
			   ((t_cell.x - m_position.x) >= 0 && (t_cell.x - m_position.x) < m_size);
	}

	[[nodiscard]] constexpr auto is_touching(const Point t_cell) const noexcept
	{
		if (m_vertical)
		{
			return ((t_cell.x - m_position.x) >= -1 && (t_cell.x - m_position.x) <= 1) &&
				   ((t_cell.y - m_position.y) >= -1 && (t_cell.y - m_position.y) <= m_size);
		}
		return ((t_cell.y - m_position.y) >= -1 && (t_cell.y - m_position.y) <= 1) &&
			   ((t_cell.x - m_position.x) >= -1 && (t_cell.x - m_position.x) <= m_size);
	}

	[[nodiscard]] constexpr auto is_alive() const noexcept { return m_cells_alive.any(); }

	auto hit(const Point t_cell) -> void;

	auto draw(Display& t_display, const Point t_offset) const -> void;

private:
	Point m_position;
	int m_size;
	std::bitset<5> m_cells_alive;
	bool m_vertical;
};
} // namespace bs

#endif // BS_SHIP_HPP
