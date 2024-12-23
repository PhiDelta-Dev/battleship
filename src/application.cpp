#include "application.hpp"

#include <charconv>
#include <iostream>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>

namespace bs
{
namespace
{
[[nodiscard]] constexpr auto string_to_point(const std::string_view t_position) noexcept
	-> std::optional<Point>
{
	if (t_position.size() != 2 && t_position.size() != 3)
	{
		return std::nullopt;
	}

	int column_number{};
	std::from_chars(&t_position.at(1), &t_position.back() + 1, column_number);

	const Point result(t_position.at(0) - 'A', column_number - 1);
	if (result.is_valid())
	{
		return result;
	}
	return std::nullopt;
}

[[nodiscard]] constexpr auto string_to_size(const std::string_view t_size) noexcept
	-> std::optional<int>
{
	int size{};
	std::from_chars(&t_size.front(), &t_size.back() + 1, size);
	if (size >= 1 && size <= 5)
	{
		return size;
	}
	return std::nullopt;
}

[[nodiscard]] constexpr auto string_to_orientation(const std::string_view t_orientation) noexcept
	-> std::optional<bool>
{
	if (t_orientation == "v" || t_orientation == "V")
	{
		return true;
	}
	if (t_orientation == "h" || t_orientation == "H")
	{
		return false;
	}
	return std::nullopt;
}
} // namespace

Application::Application()
{
	render();
	while (true)
	{
		switch (m_game_state)
		{
		case GameState::Player1Placing:
			player_1_placing();
			break;
		case GameState::Player2Placing:
			player_2_placing();
			break;
		case GameState::Player1Guessing:
			player_1_guessing();
			break;
		case GameState::Player2Guessing:
			player_2_guessing();
			break;
		}

		if (m_game_state == GameState::Player1Win || m_game_state == GameState::Player2Win)
		{
			break;
		}
		render();
	}

	if (m_game_state == GameState::Player1Win)
	{
		std::println("Player 1 wins!");
	}
	else
	{
		std::println("Player 2 wins!");
	}
}

auto Application::player_1_placing() -> void
{
	std::vector<int> sizes_available{5, 4, 3, 3, 2};

	// Keep placing ships until there are no more available
	while (!sizes_available.empty())
	{
		Point ship_position({});
		int ship_size{};
		bool ship_vertical{};

		// Keep reading the user's input until it's valid
		while (true)
		{
			// Read position
			std::print("\nPosition of Player 1's ship: ");
			std::string position_raw;
			std::getline(std::cin, position_raw);
			auto position{string_to_point(position_raw)};
			while (!position || !position.value().is_valid())
			{
				std::print("Invalid input\nPosition of Player 1's ship: ");
				std::getline(std::cin, position_raw);
				position = string_to_point(position_raw);
			}

			// Read size
			std::print("Size of Player 1's ship: ");
			std::string size_raw;
			std::getline(std::cin, size_raw);
			auto size{string_to_size(size_raw)};
			while (!size ||
				   std::ranges::find(sizes_available, size.value()) == sizes_available.end())
			{
				std::print("Invalid input\nSize of Player 1's ship: ");
				std::getline(std::cin, size_raw);
				size = string_to_size(size_raw);
			}
			const auto found_size{std::ranges::find(sizes_available, size.value())};

			// Read orientation
			std::print("Orientation of Player 1's ship: ");
			std::string orientation_raw;
			std::getline(std::cin, orientation_raw);
			auto is_vertical{string_to_orientation(orientation_raw)};
			while (!is_vertical)
			{
				std::print("Invalid input\nOrientation of Player 1's ship: ");
				std::getline(std::cin, orientation_raw);
				is_vertical = string_to_orientation(orientation_raw);
			}

			// Validate the new ship
			bool valid_placement{true};
			for (int i_cell{}; i_cell < size.value(); ++i_cell)
			{

				const auto cell{is_vertical.value()
									? Point(position.value().x, position.value().y + i_cell)
									: Point(position.value().x + i_cell, position.value().y)};
				if (!cell.is_valid())
				{
					valid_placement = false;
					break;
				}

				for (auto&& ship : m_player_1_ships)
				{
					if (ship.is_touching(cell))
					{
						valid_placement = false;
						break;
					}
				}
			}

			// Exit the loop if the new ship is valid
			if (valid_placement)
			{
				ship_position = position.value();
				ship_size = size.value();
				ship_vertical = is_vertical.value();
				sizes_available.erase(found_size);
				break;
			}
		}

		// Place the new ship
		m_player_1_ships.emplace_back(ship_position, ship_size, ship_vertical);

		render();
	}

	m_game_state = GameState::Player2Placing;
}

auto Application::player_2_placing() -> void
{
	std::vector<int> sizes_available{5, 4, 3, 3, 2};

	// Keep placing ships until there are no more available
	while (!sizes_available.empty())
	{
		Point ship_position({});
		int ship_size{};
		bool ship_vertical{};

		// Keep reading the user's input until it's valid
		while (true)
		{
			// Read position
			std::print("\nPosition of Player 2's ship: ");
			std::string position_raw;
			std::getline(std::cin, position_raw);
			auto position{string_to_point(position_raw)};
			while (!position || !position.value().is_valid())
			{
				std::print("Invalid input\nPosition of Player 2's ship: ");
				std::getline(std::cin, position_raw);
				position = string_to_point(position_raw);
			}

			// Read size
			std::print("Size of Player 2's ship: ");
			std::string size_raw;
			std::getline(std::cin, size_raw);
			auto size{string_to_size(size_raw)};
			while (!size ||
				   std::ranges::find(sizes_available, size.value()) == sizes_available.end())
			{
				std::print("Invalid input\nSize of Player 2's ship: ");
				std::getline(std::cin, size_raw);
				size = string_to_size(size_raw);
			}
			const auto found_size{std::ranges::find(sizes_available, size.value())};

			// Read orientation
			std::print("Orientation of Player 2's ship: ");
			std::string orientation_raw;
			std::getline(std::cin, orientation_raw);
			auto is_vertical{string_to_orientation(orientation_raw)};
			while (!is_vertical)
			{
				std::print("Invalid input\nOrientation of Player 2's ship: ");
				std::getline(std::cin, orientation_raw);
				is_vertical = string_to_orientation(orientation_raw);
			}

			// Validate the new ship
			bool valid_placement{true};
			for (int i_cell{}; i_cell < size.value(); ++i_cell)
			{

				const auto cell{is_vertical.value()
									? Point(position.value().x, position.value().y + i_cell)
									: Point(position.value().x + i_cell, position.value().y)};
				if (!cell.is_valid())
				{
					valid_placement = false;
					break;
				}

				for (auto&& ship : m_player_2_ships)
				{
					if (ship.is_touching(cell))
					{
						valid_placement = false;
						break;
					}
				}
			}

			// Exit the loop if the new ship is valid
			if (valid_placement)
			{
				ship_position = position.value();
				ship_size = size.value();
				ship_vertical = is_vertical.value();
				sizes_available.erase(found_size);
				break;
			}
		}

		// Place the new ship
		m_player_2_ships.emplace_back(ship_position, ship_size, ship_vertical);
		render();
	}

	m_game_state = GameState::Player1Guessing;
}

auto Application::player_1_guessing() -> void
{
	// Read guess
	std::print("\nPlayer 1's guess: ");
	std::string guess_raw;
	std::getline(std::cin, guess_raw);
	auto guess{string_to_point(guess_raw)};
	while (!guess)
	{
		std::print("Invalid input\nPlayer 1's guess: ");
		std::getline(std::cin, guess_raw);
		guess = string_to_point(guess_raw);
	}

	// Register the guess
	m_player_1_guesses.push_back(guess.value());
	for (auto&& ship : m_player_2_ships)
	{
		ship.hit(guess.value());
	}

	// Check if the game is over
	bool game_over{true};
	for (auto&& ship : m_player_2_ships)
	{
		if (ship.is_alive())
		{
			game_over = false;
			break;
		}
	}

	if (game_over)
	{
		m_game_state = GameState::Player1Win;
	}
	else
	{
		m_game_state = GameState::Player2Guessing;
	}
}

auto Application::player_2_guessing() -> void
{
	// Read guess
	std::print("\nPlayer 2's guess: ");
	std::string guess_raw;
	std::getline(std::cin, guess_raw);
	auto guess{string_to_point(guess_raw)};
	while (!guess)
	{
		std::print("Invalid input\nPlayer 2's guess: ");
		std::getline(std::cin, guess_raw);
		guess = string_to_point(guess_raw);
	}

	// Register the guess
	m_player_2_guesses.push_back(guess.value());
	for (auto&& ship : m_player_1_ships)
	{
		ship.hit(guess.value());
	}

	// Check if the game is over
	bool game_over{true};
	for (auto&& ship : m_player_1_ships)
	{
		if (ship.is_alive())
		{
			game_over = false;
			break;
		}
	}

	if (game_over)
	{
		m_game_state = GameState::Player2Win;
	}
	else
	{
		m_game_state = GameState::Player1Guessing;
	}
}

auto Application::render() -> void
{
	m_display.clear();

	m_display.draw_string({8, 0}, "My ships                  My guesses");
	m_display.draw_string({3, 2}, "A B C D E F G H I J      A B C D E F G H I J ");
	for (int i_row{0}; i_row < 9; ++i_row)
	{
		m_display.draw_character({1, 3 + i_row}, '1' + i_row);
		m_display.draw_character({26, 3 + i_row}, '1' + i_row);
	}
	m_display.draw_string({0, 12}, "10                       10");

	if (m_game_state == GameState::Player1Placing || m_game_state == GameState::Player1Guessing)
	{
		for (auto&& ship : m_player_1_ships)
		{
			ship.draw(m_display, {3, 3});
		}

		for (auto&& guess : m_player_1_guesses)
		{
			char icon{'X'};
			for (auto&& ship : m_player_2_ships)
			{
				if (ship.occupies(guess))
				{
					if (!ship.is_alive())
					{
						icon = '@';
						break;
					}
					icon = 'O';
					break;
				}
			}
			m_display.draw_character({28 + 2 * guess.x, 3 + guess.y}, icon);
		}
	}
	else if (m_game_state == GameState::Player2Placing ||
			 m_game_state == GameState::Player2Guessing)
	{
		for (auto&& ship : m_player_2_ships)
		{
			ship.draw(m_display, {3, 3});
		}

		for (auto&& guess : m_player_2_guesses)
		{
			char icon{'X'};
			for (auto&& ship : m_player_1_ships)
			{
				if (ship.occupies(guess))
				{
					if (!ship.is_alive())
					{
						icon = '@';
						break;
					}
					icon = 'O';
					break;
				}
			}
			m_display.draw_character({28 + 2 * guess.x, 3 + guess.y}, icon);
		}
	}

	m_display.print();
}
} // namespace bs

auto main() -> int
{
	bs::Application app;
	return 0;
}
