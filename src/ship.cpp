#include "ship.hpp"

namespace bs
{
auto Ship::hit(const Point t_cell) -> void
{
	if (occupies(t_cell))
	{
		if (m_vertical)
		{
			m_cells_alive.set(t_cell.y - m_position.y, false);
		}
		else
		{
			m_cells_alive.set(t_cell.x - m_position.x, false);
		}
	}
}

auto Ship::draw(Display& t_display, const Point t_offset) const -> void
{
	if (m_vertical)
	{
		for (int i_cell{0}; i_cell < m_size; ++i_cell)
		{
			const char icon{is_alive() ? (m_cells_alive.test(i_cell) ? '#' : 'O') : '@'};
			t_display.draw_character(
				{2 * m_position.x + t_offset.x, m_position.y + i_cell + t_offset.y}, icon);
		}
	}
	else
	{
		for (int i_cell{0}; i_cell < m_size; ++i_cell)
		{
			const char icon{is_alive() ? (m_cells_alive.test(i_cell) ? '#' : 'O') : '@'};
			t_display.draw_character(
				{2 * (m_position.x + i_cell) + t_offset.x, m_position.y + t_offset.y}, icon);
		}
	}
}
} // namespace bs
