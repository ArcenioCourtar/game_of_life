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
				m_live.push_back(std::make_tuple(coords, x, y));
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

// time to index things whee
void Life::go_next() {
	m_init = true;
	std::set<int64_t> test;
	for (auto iter = m_live.begin(); iter != m_live.end(); iter++) {
		REEEE test2{std::get<0>(*iter), std::get<1>(*iter), std::get<2>(*iter)};
		test.insert(std::bit_cast<int64_t>(test2));
	}
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
		Coords coords = std::bit_cast<Coords>(std::get<0>(*iter));
		std::cout <<
		"Block: " << coords.x << ' ' << coords.y <<
		" internal: " << std::get<1>(*iter) << ' ' << std::get<2>(*iter) << '\n';
	}
	std::cout << m_live.size() << '\n';
}