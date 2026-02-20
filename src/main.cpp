#include "Life.hpp"
#include <iostream>
#include <vector>
#include <iterator>

int main() {
	Life data;

	// regular setup
	data.set_node(Coords{-1, -1}, 2, 2, ALIVE, CURRENT);
	data.display_grid();
	data.go_next();
	data.go_next();
	data.go_next();
}
