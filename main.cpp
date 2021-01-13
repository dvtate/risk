#include <iostream>
#include <fstream>

#include "map.hpp"
#include "territory.hpp"
#include "globe.hpp"

int main() {

//	try {
		auto map = Map(std::ifstream("../planning/map.riskmap"));
		std::cout <<map.get_borders().size() <<std::endl;
		std::cout <<map.get_territories().size() <<std::endl;
		std::cout <<map.get_geography().size() <<std::endl;
		auto globe = Globe(map, {});
//	} catch (int e) {
//		std::cout <<e <<std::endl;
//	}
	return 0;
}
