//
// Created by tate on 10-01-21.
//

#include "state.hpp"

GameState::GameState(const MapFile& map, std::vector<Player> players = {}):
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

static bool dfs_territories(Territory* start, Territory* end, std::vector<Territory*>& rret) {
	// Base case
	if (start == end) {
		rret.emplace_back(end);
		return true;
	}

	// Recursive Case
	for (Territory* t : end->get_borders())
		if (dfs_territories(start, t, rret)) {
			rret.emplace_back(end);
			return true;
		}
	return false;
}


/**
 * Finds a path between 2 bnide
 * @param start (input) starting node for path
 * @param end (input) ending node for path
 * @return path between the nodes if found
 */
 [[nodiscard]] std::optional<std::vector<Territory*>> GameState::get_path(Territory* start, Territory* end) const {
	// TODO BFS
	std::vector<Territory*> ret;
	return dfs_territories(start, end, ret)
		? std::optional<std::vector<Territory*>>{ret}
		: std::nullopt;
}