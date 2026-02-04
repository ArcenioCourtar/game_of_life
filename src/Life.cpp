#include "Life.hpp"
#include <iterator>
#include <iostream>
#include <vector>

// Constructors

// default map will be 4 blocks big
Life::Life() : m_generation(0) {
	initialize_map();
}

// Destructors

Life::~Life() {
	// Destructor
}

void Life::initialize_map() {
	m_grid.insert({std::bit_cast<int32_t>(Coords{0, 0}), Block()});
	m_grid.insert({std::bit_cast<int32_t>(Coords{-1, 0}), Block()});
	m_grid.insert({std::bit_cast<int32_t>(Coords{-1, -1}), Block()});
	m_grid.insert({std::bit_cast<int32_t>(Coords{0, -1}), Block()});

	m_edges.left = -1; m_edges.right = 0; m_edges.up = -1; m_edges.down = 0;
}

// POGCHAMP
BlockHalf &Life::grab_gen(Block &block, bool next) {
	if (m_generation % 2 == 0 || (m_generation % 2 != 0 && next))
		return block.even;
	else
		return block.odd;
}

void Life::set_node(Coords coords, int16_t x, int16_t y, CellState state) {
	if (coords.x < m_edges.left || coords.x > m_edges.right 
		|| coords.y < m_edges.up || coords.y > m_edges.down)
	{
		std::cout << "out of current board bounds\n";
		return;
	}
	if (x < 0 || x >= BLOCK_SIZE || y < 0 || y >= BLOCK_SIZE)
	{
		std::cout << "out of current block bounds\n";
		return;
	}

	Block &block = m_grid.at(std::bit_cast<int32_t>(coords));
	BlockHalf &grid = grab_gen(block, false);
	grid[y][x] = state;
}

void Life::go_next() {
	m_generation++;
}

void Life::display_grid() {
	Block block = m_grid.at(std::bit_cast<int32_t>(Coords{m_edges.left, m_edges.up}));
	for (auto iter = block.even.begin(); iter != block.even.end(); iter++)
	{
		for(auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
			std::cout << *iter2;
		std::cout << '\n';
	}
}