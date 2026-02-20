#include "Life.hpp"
#include <iterator>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>

// Constructors

// default map will be 4 blocks big
Life::Life() : m_generation(0), m_init(false) {
	initialize_map();
}

// Destructors

Life::~Life() {
	// Destructor
}

// make variable names more clear maybe
void Life::init_block(int16_t x, int16_t y) {
	auto new_block = m_grid.insert({std::bit_cast<int32_t>(Coords{x, y}), block_t()});
	auto &block = new_block.first->second;
	for (auto iter = block.at(CURRENT).begin(); iter < block.at(CURRENT).end(); iter++)
		iter->fill(DEAD);
	for (auto iter = block.at(NEXT).begin(); iter < block.at(NEXT).end(); iter++)
		iter->fill(DEAD);
}

void Life::initialize_map() {
	init_block(0, 0);
	init_block(-1, 0);
	init_block(-1, -1);
	init_block(0, -1);

	m_edges.left = -1; m_edges.right = 0; m_edges.up = -1; m_edges.down = 0;
}

// try/catch blocks baybee
void Life::set_node(Coords coords, int16_t x, int16_t y, CellState state, Gen gen) {
	try {
		auto &block = m_grid.at(std::bit_cast<int32_t>(coords));
		try {
			block.at(at_gen(gen)).at(y).at(x) = state;
			/* This path works as intended as long as three assumptions are true:
				- Not setting a single node to "ALIVE" twice
				- All nodes you're changing are in CURRENT gen
				- not setting any nodes to "DEAD" when they've previously been set to "ALIVE"
				(I might change this behavior later)

				While testing one of these conditions might not be true,
				but in the final implementation they will be.
			*/
			if (m_init == false)
				m_live.push_back(cellinfo{coords, x, y});
			if (m_init == true) {
				// STUFF
			}
		}
		catch(const std::exception& e) {
			std::cout << "Out of block bounds\n";
		}
	}
	catch(const std::exception& e) {
		std::cout << "Block does not exist\n";
	}
}

void Life::find_surroundings(const cellinfo &info, std::set<int64_t> &list) {
	for (int16_t y = info.y - 1; y <= info.y + 1; y++) {
		for (int16_t x = info.x - 1; x <= info.x + 1; x++) {
			cellinfo info_cpy{info.c, x, y};
			if (x < 0) {info_cpy.c.x--; info_cpy.x = BLOCK_SIZE - 1;}
			if (y < 0) {info_cpy.c.y--; info_cpy.y = BLOCK_SIZE - 1;}
			if (x >= BLOCK_SIZE) {info_cpy.c.x++; info_cpy.x = 0;}
			if (y >= BLOCK_SIZE) {info_cpy.c.y++; info_cpy.y = 0;}
			list.insert(std::bit_cast<int64_t>(info_cpy));
		}
	}
}

unsigned int Life::check_surroundings(const cellinfo &info) {
	unsigned int count = 0;
	for (int16_t y = info.y - 1; y <= info.y + 1; y++) {
		for (int16_t x = info.x - 1; x <= info.x + 1; x++) {
			cellinfo info_cpy{info.c, x, y};
			if (x < 0) {info_cpy.c.x--; info_cpy.x = BLOCK_SIZE - 1;}
			if (y < 0) {info_cpy.c.y--; info_cpy.y = BLOCK_SIZE - 1;}
			if (x >= BLOCK_SIZE) {info_cpy.c.x++; info_cpy.x = 0;}
			if (y >= BLOCK_SIZE) {info_cpy.c.y++; info_cpy.y = 0;}
			try {
				[[maybe_unused]] auto &temp = 
				m_grid.at(at_gen(CURRENT)).at(std::bit_cast<int32_t>(info_cpy.c)).at(info_cpy.y).at(info_cpy.x);
				std::cout << "ey";
				if (temp == DEAD)
					std::cout << "yo";
				else
					std::cout << "oy";
			}
			catch(const std::exception& e) {  }
		}
	}
	std::cout << count << '\n';
	return count;
}

// Time to index things whee
void Life::go_next() {
	m_init = true;
	std::set<int64_t> to_be_checked;
	for (auto iter = m_live.begin(); iter != m_live.end(); iter++) {
		find_surroundings(*iter, to_be_checked);
	}
	for (auto iter = to_be_checked.begin(); iter != to_be_checked.end(); iter++) {
		[[maybe_unused]] unsigned int result = check_surroundings(std::bit_cast<cellinfo>(*iter));
	}
	
	std::cout << "To be checked amount: " << to_be_checked.size() << '\n';
	m_generation++;
}

uint32_t Life::at_gen(Gen gen) {
	return ((m_generation + gen) % 2);
}

// Slightly better than the first version. Whooo
void Life::display_grid() {
	for (int16_t y = m_edges.up; y <= m_edges.down; y++) {
		for (auto itercount = 0; itercount < BLOCK_SIZE; itercount++) {
			int16_t x = m_edges.left;
			for (; x <= m_edges.right; x++) {
				const auto &block = m_grid.at(std::bit_cast<int32_t>(Coords{x, y}));
				std::cout << std::string(
					std::begin(*(block.at(at_gen(CURRENT)).begin() + itercount)), 
					std::end(*(block.at(at_gen(CURRENT)).begin() + itercount)));
			}
			std::cout << '\n';
		}
	}
}

void Life::display_live_coords() {
	for (auto iter = m_live.begin(); iter != m_live.end(); iter++) {
		Coords coords = iter->c;
		std::cout <<
		"Block: " << coords.x << ' ' << coords.y <<
		" internal: " << iter->x << ' ' << iter->y << '\n';
	}
	std::cout << m_live.size() << '\n';
}