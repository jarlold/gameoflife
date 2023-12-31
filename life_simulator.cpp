#include <math.h>
#include <iostream>
using namespace std;

#define GRID_SIZE 512

class LifeLikeSimulator {
	bool currently_on_a = true;
	int grid_a[GRID_SIZE][GRID_SIZE];
	int grid_b[GRID_SIZE][GRID_SIZE];

	// Pointer to the grid we're currently building
	int (*future_grid)[GRID_SIZE] = grid_b;


	public: 

	virtual int kernel(int neighbors[]) { return -1; }

	// Pointer to the grid we're currently viewing
	// Public since we'll use it for drawing and whatnot
	int (*current_grid)[GRID_SIZE] = grid_a;


	void convolve(int grid[GRID_SIZE][GRID_SIZE], int x, int y, int neighbors[9]) {
		// First row
		neighbors[0] = grid[(x-1) % GRID_SIZE][(y-1) % GRID_SIZE];
		neighbors[1] = grid[ x               ][(y-1) % GRID_SIZE];
		neighbors[2] = grid[(x+1) % GRID_SIZE][(y-1) % GRID_SIZE];

		// Second row
		neighbors[3] = grid[(x-1) % GRID_SIZE][y];
		neighbors[4] = grid[ x               ][y]; // Hey that's me!
		neighbors[5] = grid[(x+1) % GRID_SIZE][y];

		// Third row
		neighbors[6] = grid[(x-1) % GRID_SIZE][(y+1) % GRID_SIZE];
		neighbors[7] = grid[ x               ][(y+1) % GRID_SIZE];
		neighbors[8] = grid[(x+1) % GRID_SIZE][(y+1) % GRID_SIZE];

	}

	void update_grid() {
		int neighbors[9];

		// Compute the next state for each cell and store it in future_grid
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				convolve(current_grid, i, j, neighbors);
				future_grid[i][j] = kernel(neighbors);
			}
		}	

		// Swap the future grid and the current grids
		if (currently_on_a) {
			current_grid = grid_b;
			future_grid = grid_a;
		} else {
			current_grid = grid_a;
			future_grid = grid_b;
		}

		currently_on_a = !currently_on_a;

	}

	void clear_grid() {
		// Go back to grid A
		currently_on_a = true;
		current_grid = grid_a;

		// Kill all the cells
		for (int i =0; i < GRID_SIZE; i++)
			for (int j =0; j < GRID_SIZE; j++)
				current_grid[i][j] = 0;
	}

	void initialize_grid() {
		clear_grid();
		// Add you code here!
		// Put whatever cool pattern or design here but modifying the 2d dimensional array!

		// Examples:
		// Randomly set living or dead
		for (int i =0; i < GRID_SIZE; i ++)
			for (int j =0; j < GRID_SIZE; j ++) 
				current_grid[i][j] = random() % 2;

		// Concentric circles
		for (int r = 0; r < 50; r += 10)
			for (int i = 0; i < 360; i++)
				current_grid[(int) (50 + (float)r * cos(i))][(int) (50 + (float)r * sin(i) )] = 1;

		// A glider
		current_grid[10][70] = 1;
		current_grid[10-1][70-2] = 1;
		current_grid[10][70-2] = 1;
		current_grid[10+1][70-2] = 1;
		current_grid[10+1][70-1] = 1;

	}

};

class LifeSimulator : public LifeLikeSimulator {

	public:
	int kernel(int neighbors[]) {
		// Count the number of neighbors
		int sum = 0;
		for (int i = 0; i < 9; i++) if (neighbors[i] == 1) sum++;

		// We'll let the compiler reduce the boolean algebra here. I'm sure it knows how...
		// if true then we are dealing with a living cell	
		if (neighbors[4] == 1) {
			// Any cell with fewer than 2+1 neighbors dies
			if (sum < 2+1) return 0;

			// Any cell with 2+1 or 3+1 lives on
			else if (sum == 2+1 || sum == 3+1 ) return 1;

			// Any cell with more than 3+1 neighbors dies
			else if (sum > 3+1 ) return 0;

		} else {
			// Any empty space with 3+0 neighbors becomes a non-empty space
			return (sum == 3) ? 1 : 0;
		}

		return 0;
	}

	LifeSimulator() {
		this->initialize_grid();
	}
};


class HighLifeSimulator : public LifeLikeSimulator {

	public:
	int kernel(int neighbors[]) {
		// Count the number of neighbors
		int sum = 0;
		for (int i = 0; i < 9; i++) if (neighbors[i] == 1) sum++;

		// We'll let the compiler reduce the boolean algebra here. I'm sure it knows how...
		// if true then we are dealing with a living cell	
		if (neighbors[4] == 1) {
			// Any cell with fewer than 2+1 neighbors dies
			if (sum < 2+1) return 0;

			// Any cell with 2+1 or 3+1 lives on
			else if (sum == 2+1 || sum == 3+1 ) return 1;

			// Any cell with more than 3+1 neighbors dies
			else if (sum > 3+1 ) return 0;

		} else {
			// Any empty space with 3+0 neighbors becomes a non-empty space
			return (sum == 3 || sum == 6) ? 1 : 0;
		}

		return 0;
	}

	HighLifeSimulator() {
		this->initialize_grid();
	}
};
