#include "Life.hpp"
#include <iostream>
#include <vector>
#include <iterator>

int main() {
	Life data;

	data.set_node(Coords{-1, -1}, 0, 0, ALIVE, NEXT);
	data.display_grid();
}
