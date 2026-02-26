#include "Life.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

void simulation_loop(Life &data) {
	std::string input;

	std::cout << INSTRUCTIONS;
	while (input.compare("exit")) {
		std::getline(std::cin, input);
		std::cout << input << '\n';
		[[maybe_unused]] int16_t count = 0;

		if (input.empty()) {
			data.display_grid(); 
			continue;
		}
	}
}

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

	simulation_loop(data);
}
