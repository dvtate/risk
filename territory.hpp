//
// Created by tate on 10-01-21.
//

#ifndef RISK_TERRITORY_HPP
#define RISK_TERRITORY_HPP

#include <string>

// player.hpp
class Player;

class Territory {

protected:
	// Territory name
	std::string _name;

	// Territories within attack range
	std::vector<Territory*> _borders;

	// Player controlling said territory (null if unoccupied)
	Player* _owner;

	// Number of troops located on territory
	unsigned short _troops;

public:
	explicit Territory(
		std::string name,
		std::vector<Territory*> borders = {},
		Player* owner = nullptr,
		unsigned short troops = 0
	):
		_name(std::move(name)), _borders(std::move(borders)), _owner(owner), _troops(troops)
	{}

	// Add a bordering territory
	void add_border(Territory* territory) {
		_borders.emplace_back(territory);
	}

	// Getters
	[[nodiscard]] const auto& get_borders() const {
		return _borders;
	}
	[[nodiscard]] const auto& get_name() const {
		return _name;
	}
	[[nodiscard]] const auto& get_owner() const {
		return _owner;
	}
	[[nodiscard]] const auto& get_troops() const {
		return _troops;
	}

	// When user attempts to conquer a territory using troops on this one
	enum class AttackType { SINGLE, DOUBLE, TRIPLE, CLASSIC, BLITZ };
	bool attack(Territory& enemy, AttackType type);
};

#endif //RISK_TERRITORY_HPP
