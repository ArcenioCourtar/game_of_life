#include "Life.hpp"
#include <iterator>
#include <iostream>

// Constructors

// default map will be 4 blocks big
Life::Life() : m_generation(0) {
	std::cout << m_grid.size() << '\n';
	initialize_map();
	std::cout << m_grid.size() << '\n';
}

// Destructors

Life::~Life() {
	// Destructor
}

void Life::initialize_map() {
	m_grid.insert({std::bit_cast<int32_t>(Coords{0, 0}), Block()});
	m_grid.insert({std::bit_cast<int32_t>(Coords{-1, 0}), Block()});
	m_grid.insert({std::bit_cast<int32_t>(Coords{1, -1}), Block()});
	m_grid.insert({std::bit_cast<int32_t>(Coords{0, -1}), Block()});

	m_edges.left = -1; m_edges.right = 0; m_edges.up = 0; m_edges.down = -1;
}

// void Life::set_node(int32_t block, int16_t x, int16_t y, CellState state) {
	
// }