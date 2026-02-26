#include "Life.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "please pass file to parse\n";
		return (0);
	}
	std::ifstream file;
	file.open(argv[1]);
	if (!file.is_open()) {
		std::cout << "can't open file xd\n";
		return (0);
	}
	Life data;
	data.parse_file(file);
	data.initialize_map();

	data.display_grid();
	data.go_next();
	data.display_grid();
	data.go_next();
	data.display_grid();
	data.go_next();
	data.display_grid();
}
