#pragma once
#include <unordered_map>	// map
#include <utility>			// pair
#include <set>				// set
#include <tuple>			// tuple
#include <vector>			// vector
#include <array>			// arrays with iterators baybee
#include <cstdint>			// force integer sizes of specific size
#include <bit>
#include <fstream>
#define BLOCK_SIZE 8

// This REALLY shouldn't be stored in a single class. But I'm trying to interact with C++ features y'all

enum CellState { DEAD = '0', ALIVE = '1' };
enum Gen { CURRENT = 0, NEXT = 1 };

// x y order
struct Coords {
	int16_t x;
	int16_t y;

	bool operator==(const Coords &s) const {
		return (x == s.x && y == s.y);
	}
};

struct cellinfo {
	Coords c;
	int16_t x;
	int16_t y;

	bool operator==(const cellinfo &s) const {
		return (c == s.c && x == s.x && y == s.y);
	}
};

// [y][x] For more efficient traversal of the grid
// I hate this lmao, but it works?
typedef std::array<std::array<std::array<CellState, BLOCK_SIZE>, BLOCK_SIZE>, 2> block_t;

// defines edges of current board
/*
		up
	left	right ->
		down
		|
		V
*/
struct Edges {
	int16_t left;
	int16_t right;
	int16_t up;
	int16_t down;
};

class Life {
	public:
		Life( void );
		Life(const Life& src) = delete;

		Life& operator=(const Life& src) = delete;

		~Life();

		// set node locating block and picking coords in there
		void set_node(Coords coords, int16_t x, int16_t y, CellState state, Gen gen);
		// convert "raw" coords into one that adheres to the block structure
		// somefunction()

		// go next
		void go_next();
		// display entire grid
		void display_grid();
		// display specific section of grid
		void display_grid(int16_t left, int16_t right, int16_t down, int16_t up);
		// display live node coordinates
		void display_live_coords();
		// assign nodes from parsing input file
		void parse_file(std::ifstream &file);

		void initialize_map();
		// placeholder for testing random bs
		void test_f();


	private:
		std::vector<cellinfo> m_live;
		std::unordered_map<int32_t, block_t> m_grid;
		Edges m_edges;
		uint32_t m_generation;
		bool m_init;
		
		uint32_t at_gen(Gen gen);
		// initialize block
		void init_block(int16_t x, int16_t y);
		// locate and store 9 surrounding tiles
		void find_surroundings(const cellinfo &info, std::set<int64_t> &list);
		// count live tiles surrounding target location
		unsigned int check_surroundings(const cellinfo &info);
		// expand map when an edge is reached and a cell across the edge becomes live
		void expand_map();
		// convert global coords to coords in accordance to block structure
		cellinfo convert_coords(int16_t x, int16_t y);

		// print location of live cells
		void get_live_cells();
};

