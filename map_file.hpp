//
// Created by tate on 11-01-21.
//

#ifndef RISK_MAP_FILE_HPP
#define RISK_MAP_FILE_HPP

#include <vector>
#include <utility>	// pair
#include <string>
#include <iostream>
#include <cinttypes>
#include <optional>

/**
 * @class describes a custom map
 * Probably should reconsider how the geography is handled since using terminal UI isn't realistic for reasonably-sized maps
 */
class MapFile {
public:
	using index_t = uint8_t;

protected:
	std::string _geography;
	std::vector<std::pair<uint8_t, uint8_t>> _borders;
	std::vector<std::string> _territories;

public:
	explicit MapFile(std::istream&& is);

	enum class Failure { FORMAT, STREAM };

	[[nodiscard]] inline const std::string& get_geography() const {
		return _geography;
	}
	[[nodiscard]] inline const auto& get_borders() const {
		return _borders;
	}
	[[nodiscard]] inline const auto& get_territories() const {
		return _territories;
	}
};
#endif //RISK_MAP_FILE_HPP
