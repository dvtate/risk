//
// Created by tate on 10-01-21.
//

#include "globe.hpp"

Globe::Globe(const Map& map, std::vector<Player> players = {}):
	_players(std::move(players))
{
	// Make territory objects
	_territories.reserve(map.get_territories().size());
	for (const auto& name : map.get_territories())
		_territories.emplace_back(Territory(name));

	// Make border links
	for (const auto& border : map.get_borders()) {
		_territories[border.first].add_border(&_territories[border.second]);
		_territories[border.second].add_border(&_territories[border.first]);
	}

	_geography = map.get_geography();
}

[[nodiscard]] std::optional<std::vector<Territory*>> Globe::get_path(const Territory*, const Territory*) const {
	// TODO BFS
	std::vector<Territory*> ret;
}