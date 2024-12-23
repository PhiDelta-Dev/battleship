#ifndef BS_DISPLAY_HPP
#define BS_DISPLAY_HPP

#include <array>
#include <string_view>

#include "point.hpp"

namespace bs
{
class Display
{
public:
	constexpr Display() { m_cells.fill(' '); }

	auto clear() -> void;
	auto draw_character(Point t_cell, char t_character) -> void;
	auto draw_string(Point t_cell, std::string_view t_string) -> void;
	auto print() -> void;

private:
	static constexpr std::size_t line_width{50}, line_count{13};
	std::array<char, line_count * line_width> m_cells;
};
} // namespace bs

#endif // BS_DISPLAY_HPP
