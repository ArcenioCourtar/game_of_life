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

// make variable names more clear maybe
void Life::init_block(int16_t x, int16_t y) {
	auto new_block = m_grid.insert({std::bit_cast<int32_t>(Coords{x, y}), Block()});
	auto &block = new_block.first->second;
	for (auto iter = block.gen.at(0).begin(); iter < block.gen.at(0).end(); iter++)
		iter->fill(DEAD);
	for (auto iter = block.gen.at(1).begin(); iter < block.gen.at(1).end(); iter++)
		iter->fill(DEAD);
}

void Life::initialize_map() {
	init_block(0, 0);
	init_block(-1, 0);
	init_block(-1, -1);
	init_block(0, -1);

	m_edges.left = -1; m_edges.right = 0; m_edges.up = -1; m_edges.down = 0;
}

void Life::set_node(Coords coords, int16_t x, int16_t y, CellState state, Gen gen) {
	if (coords.x < m_edges.left || coords.x > m_edges.right || coords.y < m_edges.up || coords.y > m_edges.down)
	{
		std::cout << "out of current board bounds\n";
		return;
	}
	if (x < 0 || x >= BLOCK_SIZE || y < 0 || y >= BLOCK_SIZE)
	{
		std::cout << "out of current block bounds\n";
		return;
	}

	auto &block = m_grid.at(std::bit_cast<int32_t>(coords));
	block.gen.at(at_gen(gen))[y][x] = state;
}

void Life::go_next() {
	// for (auto iter1 = m_grid.begin(); iter1 != m_grid.end(); iter1++)
	// {
	// 	for (auto iter2 = iter1->second.gen.at(CURRENT).begin(); 
	// 		iter2 != iter1->second.gen.at(CURRENT).end(); iter2++)
	// 	{
	// 		for (auto)
	// 	}
	// }
	// m_generation++;
}

uint32_t Life::at_gen(Gen gen) {
	return ((m_generation + gen) % 2);
}

// Slightly better than the first version. Whooo
void Life::display_grid() {
	std::string str;
	str.reserve(BLOCK_SIZE * (m_edges.right - m_edges.left) + 1);

	for (int16_t y = m_edges.up; y <= m_edges.down; y++)
	{
		for (auto itercount = 0; itercount < BLOCK_SIZE; itercount++)
		{
			int16_t x = m_edges.left;
			for (; x <= m_edges.right; x++)
			{
				const auto &block = m_grid.at(std::bit_cast<int32_t>(Coords{x, y}));
				str += std::string(
					std::begin(*(block.gen.at(at_gen(CURRENT)).begin() + itercount)), 
					std::end(*(block.gen.at(at_gen(CURRENT)).begin() + itercount)));
			}
			std::cout << str << '\n';
			str.erase();
		}
	}
}
