#include "Life.hpp"
#include <iterator>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <string>

// Constructors

// default map will be 4 blocks big
Life::Life() : m_edges(Edges{0, 0, 0, 0}), m_generation(0), m_init(false) {}

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
	if (x > m_edges.right)
		m_edges.right = x;
	if (x < m_edges.left)
		m_edges.left = x;
	if (y > m_edges.down)
		m_edges.down = y;
	if (y < m_edges.up)
		m_edges.right = y;
}

void Life::initialize_map() {
	for (auto iter = m_live.begin(); iter != m_live.end(); iter++) {
		if (m_grid.find(std::bit_cast<int32_t>(iter->c)) == m_grid.end())
			init_block(iter->c.x, iter->c.y);
		set_node(iter->c, iter->x, iter->y, ALIVE, CURRENT);
	}
}

// try/catch blocks baybee
void Life::set_node(Coords coords, int16_t x, int16_t y, CellState state, Gen gen) {
	try {
		auto &block = m_grid.at(std::bit_cast<int32_t>(coords));
		try {
			block.at(at_gen(gen)).at(y).at(x) = state;
			if (m_init == true) {
				if (block.at(at_gen(CURRENT)).at(y).at(x) == ALIVE) {
					if (state == DEAD)
						m_live.erase(std::find(m_live.begin(), m_live.end(), cellinfo{coords, x, y}));
				} else {
					if (state == ALIVE)
						m_live.push_back(cellinfo{coords, x, y});
				}
			}
		}
		catch(const std::exception& e) {
			// std::cout << "Out of block bounds\n";
		}
	}
	catch(const std::exception& e) {
		init_block(coords.x, coords.y);
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
				auto &temp = 
				m_grid.at(std::bit_cast<int32_t>(info_cpy.c)).at(at_gen(CURRENT)).at(info_cpy.y).at(info_cpy.x);
				if (std::bit_cast<int64_t>(info_cpy) == std::bit_cast<int64_t>(info))
					continue;
				if (temp == ALIVE)
					count++;
			}
			catch(const std::exception& e) { }
		}
	}
	return count;
}

// Time to index things whee
void Life::go_next() {
	m_init = true;
	std::set<int64_t> to_be_checked;
	for (auto iter = m_live.begin(); iter != m_live.end(); iter++)
		find_surroundings(*iter, to_be_checked);
	for (auto iter = to_be_checked.begin(); iter != to_be_checked.end(); iter++) {
		cellinfo info{std::bit_cast<cellinfo>(*iter)};
		[[maybe_unused]] unsigned int result = check_surroundings(info);
		if (m_grid.at(std::bit_cast<int32_t>(info.c)).at(at_gen(CURRENT)).at(info.y).at(info.x) == ALIVE) {
			if (result < 2 || result > 3)
				set_node(info.c, info.x, info.y, DEAD, NEXT);
			else
				set_node(info.c, info.x, info.y, ALIVE, NEXT);
		} else {
			if (result == 3)
				set_node(info.c, info.x, info.y, ALIVE, NEXT);
			else
				set_node(info.c, info.x, info.y, DEAD, NEXT);
		}
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
		Coords coords = iter->c;
		std::cout <<
		"Block: " << coords.x << ' ' << coords.y <<
		" internal: " << iter->x << ' ' << iter->y << '\n';
	}
	std::cout << m_live.size() << '\n';
}

void Life::parse_file(std::ifstream &file) {
	int16_t xcount = 0, ycount = 0;
	std::string str;
	while (std::getline(file, str)) {
		xcount = 0;
		for (auto iter = str.begin(); iter != str.end(); iter++) {
			if ((*iter) == '1')
				m_live.push_back(convert_coords(xcount, ycount));
			xcount++;
		}
		ycount++;
	}
}

cellinfo Life::convert_coords(int16_t x, int16_t y) {
	return (cellinfo{
		Coords{static_cast<int16_t>(x / BLOCK_SIZE), static_cast<int16_t>(y / BLOCK_SIZE)}, 
		static_cast<int16_t>(x % BLOCK_SIZE), static_cast<int16_t>(y % BLOCK_SIZE)});
}