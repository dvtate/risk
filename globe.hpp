//
// Created by tate on 10-01-21.
//

#ifndef RISK_GLOBE_HPP
#define RISK_GLOBE_HPP

#include <vector>
#include <algorithm>

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
	explicit Globe(const Map&, std::vector<Player>);

	/**
	 * Convert a territory pointer into it's index in this->_territories
	 * @param t - relevant territory pointer
	 * @return
	 */
	Map::index_t get_index(const Territory const* t) const {
		return static_cast<Map::index_t>(t - &_territories[0]);
	}

	[[nodiscard]] std::optional<std::vector<Territory*>> get_path(const Territory*, const Territory*) const;
	[[nodiscard]] std::optional<std::vector<Map::index_t>> get_path(const Map::index_t a, const Map::index_t b) const {
		const auto path = get_path(&_territories[a], &_territories[b]);
		if (!path)
			return std::nullopt;
		std::vector<Map::index_t> ret;
		ret.reserve(path->size());
		for (auto* t : *path)
			ret.emplace_back(get_index(t));
		return ret;
	}
};


#endif //RISK_GLOBE_HPP