//
// Created by tate on 10-01-21.
//

#ifndef RISK_STATE_HPP
#define RISK_STATE_HPP

#include <vector>
#include <algorithm>

#include "territory.hpp"
#include "map_file.hpp"
#include "player.hpp"

class GameState {
protected:
	// Plots of land
	std::vector<Territory> _territories;

	// Game players
	std::vector<Player> _players;

	// Template
	std::string _geography;

	// Index of player who's turn it is
	uint8_t _player_index{0};

public:
	explicit GameState(const MapFile&, std::vector<Player>);

	/**
	 * Convert a territory pointer into it's index in this->_territories
	 * @param t - relevant territory pointer
	 * @return
	 */
	MapFile::index_t get_index(const Territory* t) const {
		return static_cast<MapFile::index_t>(t - &_territories[0]);
	}

	Territory& get_territory(const MapFile::index_t index) {
		return this->_territories[index];
	}

	inline const Player& current_player() const {
		return this->_players[this->_player_index];
	}

	/**
	 * Find path between two territories if it exists
	 */
	[[nodiscard]] std::optional<std::vector<Territory*>> get_path(Territory* start, Territory* end) const;
	[[nodiscard]] std::optional<std::vector<MapFile::index_t>> get_path(const MapFile::index_t a, const MapFile::index_t b) {
		const auto path = get_path(&_territories[a], &_territories[b]);
		if (!path)
			return std::nullopt;
		std::vector<MapFile::index_t> ret;
		ret.reserve(path->size());
		for (auto* t : *path)
			ret.emplace_back(get_index(t));
		return ret;
	}

	[[nodiscard]] std::vector<MapFile::index_t> unoccupied_territories() const {
		std::vector<MapFile::index_t> ret;
		const MapFile::index_t l = this->_territories.size();
		for (MapFile::index_t i = 0; i < l; i++)
			if (this->_territories[i].get_owner() == nullptr)
				ret.emplace_back(i);
		return ret;
	}

	[[nodiscard]] std::vector<MapFile::index_t> player_territories() const {
		std::vector<MapFile::index_t> ret;
		const MapFile::index_t l = this->_territories.size();
		for (MapFile::index_t i = 0 ; i < l; i++)
			if (this->_territories[i].get_owner() == &this->current_player())
				ret.emplace_back(i);
		return ret;
	}

	[[nodiscard]] auto attack_moves(
		const std::vector<MapFile::index_t>& territories
	) const {
		std::vector<std::pair<MapFile::index_t, MapFile::index_t>> ret;
		for (const auto& ti: territories)
			for (const auto* tp: this->_territories[ti].get_borders())
				ret.emplace_back(std::make_pair(ti, this->get_index(tp)));
		return ret;
	}
	[[nodiscard]] auto attack_moves() const {
		return this->attack_moves(this->player_territories());
	}

	[[nodiscard]] auto fortify_start_options() const {
		auto ret = this->player_territories();
		std::copy_if(ret.begin(), ret.end(), ret.begin(), [this](int i) {
			return !this->_territories[i].get_borders().empty();
		});
		return ret;
	}
};


#endif //RISK_STATE_HPP