#ifndef BS_APPLICATION_HPP
#define BS_APPLICATION_HPP

#include <vector>

#include "display.hpp"
#include "ship.hpp"

namespace bs
{
class Application
{
public:
	Application();

	auto player_1_placing() -> void;
	auto player_2_placing() -> void;
	auto player_1_guessing() -> void;
	auto player_2_guessing() -> void;

	auto render() -> void;

private:
	enum class GameState
	{
		Player1Placing,
		Player2Placing,
		Player1Guessing,
		Player2Guessing,
		Player1Win,
		Player2Win
	};

	Display m_display;
	std::vector<Point> m_player_1_guesses, m_player_2_guesses;
	std::vector<Ship> m_player_1_ships, m_player_2_ships;
	GameState m_game_state{GameState::Player1Placing};
};
} // namespace bs

#endif // BS_APPLICATION_HPP
