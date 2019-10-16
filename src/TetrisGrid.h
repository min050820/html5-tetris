#ifndef TETRIS_GRID_H_
#define TETRIS_GRID_H_


struct SDL_Rect;
class ProgramState;

enum class Tetrimino : unsigned char {
	EMPTY = 0,
	I, O, T, S, Z, J, L
};


class TetrisGrid {
	// [0][0] = 왼쪽 아래
	Tetrimino grid[40][10];

public:
	TetrisGrid();
	void render(ProgramState& state, SDL_Rect boundary);
	void update(ProgramState& state);
};


#endif