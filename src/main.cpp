#include "Life.hpp"
#include <iostream>
#include <vector>
#include <iterator>

int main() {
	Life data;

	// regular setup
	data.set_node(Coords{0, 0}, 0, 0, ALIVE, CURRENT);
	data.set_node(Coords{0, 0}, 1, 0, ALIVE, CURRENT);
	data.set_node(Coords{0, 0}, 2, 0, ALIVE, CURRENT);
	data.set_node(Coords{0, 0}, 1, 1, ALIVE, CURRENT);
	data.set_node(Coords{0, 0}, 2, 1, ALIVE, CURRENT);
	data.set_node(Coords{0, 0}, 3, 1, ALIVE, CURRENT);
	data.display_grid();
	data.display_live_coords();
	data.go_next();
	data.display_grid();
	data.display_live_coords();
	data.go_next();
	data.display_grid();
	data.display_live_coords();
	data.go_next();
	data.display_grid();
	data.display_live_coords();
}
