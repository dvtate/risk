//
// Created by tate on 11-01-21.
//

#include <sstream>

#include "map_file.hpp"

MapFile::MapFile(std::istream&& is) {
	if (!is)
		throw MapFile::Failure::STREAM;

	// Verify start
	std::string line;
	std::getline(is, line);

	const auto invalid_format = -1;
	if (line != "territories:")
		throw MapFile::Failure::FORMAT;

	// Read territory names
	while (!!is) {
		std::getline(is, line);
		if (line == "borders:")
			break;
		_territories.emplace_back(line);
	}
	if (line != "borders:")
		throw MapFile::Failure::FORMAT;

	// Read borders
	while (!!is) {
		std::getline(is, line);
		if (line == "map:")
			break;
		int a, b;
		std::istringstream(line) >> a >> b;
		_borders.emplace_back(std::pair(a, b));
	}
	if (line != "map:")
		throw MapFile::Failure::FORMAT;

	// Read map
	while (!!std::getline(is, line))
		_geography += line + '\n';

	// TODO add territories outlines for cards
}