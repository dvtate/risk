#include <iostream>
#include <fstream>

#include "map_file.hpp"
#include "territory.hpp"
#include "state.hpp"

int main() {

//	try {
		auto map = MapFile(std::ifstream("../planning/map.riskmap"));
		std::cout <<map.get_borders().size() <<std::endl;
		std::cout <<map.get_territories().size() <<std::endl;
		std::cout <<map.get_geography().size() <<std::endl;
		auto globe = GameState(map, {});
//	} catch (int e) {
//		std::cout <<e <<std::endl;
//	}
	return 0;
}
