#pragma once
#include <unordered_map>	// map
#include <utility>			// pair
#include <cstdint>			// force integer sizes of specific size
#include <bit>
#define BLOCK_SIZE 16

enum CellState { DEAD = 0, ALIVE = 1 };

struct EvenOdd {
	CellState even;
	CellState odd;
} ;

struct Block {
	EvenOdd cell[BLOCK_SIZE][BLOCK_SIZE] = { };
};

struct Coords {
	int16_t x;
	int16_t y;
};

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

	private:
		std::unordered_map<int32_t, Block> m_grid;
		Edges m_edges;
		uint32_t m_generation;
		

		// initial 4 blocks
		void initialize_map();
		// expand map when an edge is reached and a cell across the edge becomes live
		void expand_map();

		// set node using global coordinates
		void set_node(int16_t x, int16_t y, CellState state);
		// set node locating block and picking coords in there
		void set_node(int32_t block, int16_t x, int16_t y, CellState state);
		// convert "raw" coords into one that adheres to the block structure
		// somefunction()

		// go next
		void go_next();
		// display grid
		void display_grid();
		// print location of live cells
		void get_live_cells();
};

