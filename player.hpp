//
// Created by tate on 11-01-21.
//

#ifndef RISK_PLAYER_HPP
#define RISK_PLAYER_HPP

#include <string>

/**
 * User for online games?
 */
class User {
	std::string _name;

public:
	explicit User(std::string name): _name(std::move(name)) {}

	[[nodiscard]] const auto& get_name() const {
		return _name;
	}
};

/**
 * Player participating in active game
 */
class Player {
public:
	enum class Color { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE	};

protected:
	// TODO Should probably instead link to User object but too soon for that rn
	std::string _name;
	Color _color;

public:
	Player(std::string name, Color color): _name(std::move(name)), _color(color) {}

	[[nodiscard]] const auto& get_name() const {
		return _name;
	}
	const auto& get_color() const {
		return _color;
	}
};


#endif //RISK_PLAYER_HPP
