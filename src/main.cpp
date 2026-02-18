#include "Life.hpp"
#include <iostream>
#include <vector>
#include <iterator>

int main() {
	Life data;

	// regular setup
	data.set_node(Coords{-1, -1}, 0, 0, ALIVE, CURRENT);
	data.set_node(Coords{-1, -1}, 1, 1, ALIVE, CURRENT);
	data.set_node(Coords{-1, -1}, 2, 2, ALIVE, CURRENT);
	data.set_node(Coords{-1, -1}, 3, 3, ALIVE, CURRENT);
	data.set_node(Coords{0, -1}, 0, 0, ALIVE, CURRENT);
	data.set_node(Coords{0, -1}, 1, 0, ALIVE, CURRENT);
	data.set_node(Coords{0, -1}, 2, 0, ALIVE, CURRENT);
	data.set_node(Coords{-1, 0}, 3, 0, ALIVE, CURRENT);
	data.set_node(Coords{-1, 0}, 3, 1, ALIVE, CURRENT);
	data.set_node(Coords{-1, 0}, 3, 2, ALIVE, CURRENT);
	data.display_grid();
	data.display_live_coords();
}
