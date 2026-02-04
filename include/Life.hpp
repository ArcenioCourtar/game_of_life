#pragma once
#include <unordered_map>	// map
#include <utility>			// pair
#include <array>			// arrays with iterators baybee
#include <cstdint>			// force integer sizes of specific size
#include <bit>
#define BLOCK_SIZE 4

enum CellState { DEAD = 0, ALIVE = 1 };
enum Gen { CURRENT = 0, NEXT = 1 };

typedef std::array<std::array<CellState, BLOCK_SIZE>, BLOCK_SIZE> BlockHalf;

// [y][x] For more efficient traversal of the grid
struct Block {
	std::array<std::array<CellState, BLOCK_SIZE>, BLOCK_SIZE> even = { };
	std::array<std::array<CellState, BLOCK_SIZE>, BLOCK_SIZE> odd = { };
};

// x y order
struct Coords {
	int16_t x;
	int16_t y;
};

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

		// set node using global coordinates
		void set_node(int16_t x, int16_t y, CellState state);
		// set node locating block and picking coords in there
		void set_node(Coords coords, int16_t x, int16_t y, CellState state);
		// convert "raw" coords into one that adheres to the block structure
		// somefunction()

		// go next
		void go_next();
		// display entire grid
		void display_grid();
		// display specific section of grid
		void display_grid(int16_t left, int16_t right, int16_t down, int16_t up);

		// placeholder for testing random bs
		void test_f();


	private:
		std::unordered_map<int32_t, Block> m_grid;
		Edges m_edges;
		uint32_t m_generation;
		

		// initial 4 blocks
		void initialize_map();
		// expand map when an edge is reached and a cell across the edge becomes live
		void expand_map();
		// get reference to correct map version
		BlockHalf &grab_gen(Block &block, bool next);


		// print location of live cells
		void get_live_cells();
};

