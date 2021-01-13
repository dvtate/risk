//
// Created by tate on 11-01-21.
//

#ifndef RISK_MAP_HPP
#define RISK_MAP_HPP

#include <vector>
#include <utility>	// pair
#include <string>
#include <iostream>
#include <cinttypes>

/**
 * This class describes a custom map
 */
class Map {
protected:
	std::string _geography;
	std::vector<std::pair<uint8_t, uint8_t>> _borders;
	std::vector<std::string> _territories;

public:
	explicit Map(std::istream&& is);

	enum class Failure { FORMAT, STREAM };

	const std::string& get_geography() const {
		return _geography;
	}
	const auto& get_borders() const {
		return _borders;
	}
	const auto& get_territories() const {
		return _territories;
	}
};
#endif //RISK_MAP_HPP
