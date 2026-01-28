#pragma once
#include <vector>
#define DEFAULT_DIM 50

enum CellState { DEAD, ALIVE };

class Life {
	public:
		Life(void);
		Life(const Life& src) = delete;
		Life& operator=(const Life& src) = delete;

		~Life();

		void advanceState();

	private:
		int dimensions;

		std::vector<CellState> current;
		std::vector<CellState> next;
};
