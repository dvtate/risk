//
// Created by tate on 10-01-21.
//

#ifndef RISK_GLOBE_HPP
#define RISK_GLOBE_HPP

#include <vector>

#include "territory.hpp"
#include "map.hpp"
#include "player.hpp"

class Globe {
protected:
	// Plots of land
	std::vector<Territory> _territories;

	// Game players
	std::vector<Player> _players;

	// Template
	std::string _geography;

public:
	explicit Globe(const Map, const std::vector<Player>);
};


#endif //RISK_GLOBE_HPP