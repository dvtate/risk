//
// Created by tate on 10-01-21.
//

#include <random>
#include <algorithm>

#include "territory.hpp"


// Outcome of a fair dice roll
static uint8_t dice_roll() {
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<unsigned short> dist(1, 6);
	return dist(gen);
}

// Max value from N dice rolls
static uint8_t max_dice_roll(uint8_t n) {
	uint8_t ret = 0;
	for (; n > 0; --n) {
		const auto v = dice_roll();
		if (v > ret)
			ret = v;
	}
	return ret;
}

static std::vector<uint8_t> multi_dice(uint8_t n, const bool sort = true) {
	std::vector<uint8_t> ret(n);
	for (; n > 0; --n)
		ret[n] = dice_roll();

	if (sort)
		std::sort(ret.begin(), ret.end());
	return ret;
}

// TODO might be good to display actual dice to UI like orig game eventually
bool Territory::attack(Territory& enemy, const Territory::AttackType type) {
	// Cannot attack with only one army
	if (_troops <= 1)
		return false;

	// Maximum number of dice available
	const int enemy_dice = enemy._troops > 3 ? 3 : enemy._troops <= 2 ? 1 : 2;
	const int max_dice = _troops > 3 ? 3 : _troops <= 2 ? 1 : 2;

	// Handle different attack types
	switch (type) {
		// Attack enemy with 3 dice
		case Territory::AttackType::TRIPLE:
			if (max_dice >= 3) {
				auto dice = multi_dice(max_dice);
				const auto edice = multi_dice(enemy_dice);
				for (uint8_t v : edice) {
					if (dice.back() > v)
						--enemy._troops;
					else
						--_troops;
					dice.pop_back();
				}
				break;
			} // else user can't use this mode

		// Attack enemy with 2 dice
		case Territory::AttackType::DOUBLE:
			if (max_dice >= 2) {
				// TODO improve algorithm
				auto dice = multi_dice(2);
				auto edice = multi_dice(enemy_dice);
				for (uint_fast8_t i = 0; i < 2; ++i) {
					const auto v = edice.back();
					edice.pop_back();
					if (dice.back() > v)
						--enemy._troops;
					else
						--_troops;
					dice.pop_back();
				}
				break;
			}

		// Attack enemy with one dice
		case Territory::AttackType::SINGLE: {
			const auto v = dice_roll();
			const auto edice = multi_dice(enemy_dice);
			if (v >= edice.back())
				--enemy._troops;
			else
				--_troops;

			break;
		};

		// Shortcut for rolling dice until someone looses
		case Territory::AttackType::CLASSIC:
			while (_troops > 1 && enemy._troops > 1)
				this->attack(enemy, Territory::AttackType::TRIPLE);
			break;

		// Similar to hasbro's balanced blitz mode
		//  eliminates unlikely scenarios
		case Territory::AttackType::BLITZ: {
			// TODO implement
			return false;
			break;
		};
	}

	// If we killed enemy, occupy their territory
	if (enemy._troops == 0) {
		enemy._troops = 1;
		enemy._owner = _owner;
		_troops -= 1;
		return true;
	}
	return false;
}