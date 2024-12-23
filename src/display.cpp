#include "display.hpp"

#include <print>

namespace bs
{
auto Display::clear() -> void
{
	m_cells.fill(' ');
	std::system("cls");
}

auto Display::draw_character(const Point t_cell, const char t_character) -> void
{
	const auto cell_index{t_cell.y * line_width + t_cell.x};
	if (cell_index < m_cells.size())
	{
		m_cells.at(cell_index) = t_character;
	}
}

auto Display::draw_string(const Point t_cell, const std::string_view t_string) -> void
{
	const auto cell_index{t_cell.y * line_width + t_cell.x};
	if (cell_index + t_string.size() <= m_cells.size())
	{
		std::memcpy(&m_cells.at(t_cell.y * line_width + t_cell.x), t_string.data(),
					t_string.size());
	}
}

auto Display::print() -> void
{
	for (std::size_t i_line{0}; i_line < line_count; ++i_line)
	{
		const std::string_view line_view(&m_cells.at(i_line * line_width), line_width);
		std::println("{}", line_view);
	}
}
} // namespace bs
