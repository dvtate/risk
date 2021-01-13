//
// Created by tate on 11-01-21.
//

#ifndef RISK_PLAYER_HPP
#define RISK_PLAYER_HPP

#include <string>

/**
 * User for online games
 */
class User {
	std::string _name;

public:
	explicit User(const std::string name): _name(name) {}

	const auto& get_name() {
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
	Player(const std::string name, Color color): _name(name), _color(color) {}

	const auto& get_name() const {
		return _name;
	}
	const auto& get_color() const {
		return _color;
	}
};


#endif //RISK_PLAYER_HPP
