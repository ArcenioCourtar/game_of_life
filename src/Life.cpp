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
	for (auto iter = block.even.begin(); iter != block.even.end(); iter++)
		iter->fill(DEAD);
	for (auto iter = block.odd.begin(); iter != block.odd.end(); iter++)
		iter->fill(DEAD);
}

void Life::initialize_map() {
	init_block(0, 0);
	init_block(-1, 0);
	init_block(-1, -1);
	init_block(0, -1);

	m_edges.left = -1; m_edges.right = 0; m_edges.up = -1; m_edges.down = 0;
}

// POGCHAMP
BlockHalf &Life::grab_gen(Block &block, Gen gen) {
	if ((m_generation % 2 == 0 && gen == CURRENT)|| (m_generation % 2 != 0 && gen == NEXT))
		return block.even;
	else
		return block.odd;
}

void Life::set_node(Coords coords, int16_t x, int16_t y, CellState state, Gen gen) {
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

	BlockHalf &block = grab_gen(m_grid.at(std::bit_cast<int32_t>(coords)), gen);
	block[y][x] = state;
}

void Life::go_next() {
	m_generation++;
}

// surely there's a more elegant way to do this lol
void Life::display_grid() {
	std::string str;
	Coords coords;
	
	for (coords.y = m_edges.up; coords.y <= m_edges.down; coords.y++)
	{
		for (uint16_t itercount = 0; itercount < BLOCK_SIZE; itercount++) // can I use iterators here too? surely.
		{
			for (coords.x = m_edges.left; coords.x <= m_edges.right; coords.x++)
			{
				BlockHalf block = grab_gen(m_grid.at(std::bit_cast<int32_t>(coords)), CURRENT);
				str += std::string(std::begin(*(block.begin() + itercount)), std::end(*(block.begin() + itercount)));
			}
			std::cout << str << '\n';
			str.clear();
		}
	}
}