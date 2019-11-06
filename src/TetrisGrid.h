#ifndef TETRIS_GRID_H_
#define TETRIS_GRID_H_


#include "Tetrimino.h"

struct SDL_Rect;
class ProgramState;
class MainGameScreen;


class TetrisGrid {
public:
	TetrisGrid();
	void render(ProgramState& state, SDL_Rect boundary);
	void update(ProgramState& state);
	bool isNewFallingShapeRequired();
	void pushNewFallingShape(TetriminoShape newShape);

	void doHardDrop();
	void doSoftDrop();
	void doRotateCW();
	void doRotateCCW();
	void doMoveLeft();
	void doMoveRight();

private:
	void _updateFallingShape(ProgramState& state);
	int _updateClearLine();
	void _tryRotateShape(bool isClockwise);
	bool _fallingRotateShape(int xDisp, int yDisp, bool isClockwise);
	void _fallingLockShape();
	bool _fallingCheckOverlap();
	bool _fallingBottomBlocked();

private:
	// [0][0] = 왼쪽 아래
	TetriminoBlock _grid[40][10];

	TetriminoShape _fallingShape;
	int _fallingRotation, _fallingY, _fallingX;
	float _fallingTimer;
	int _fallingBlockedCount;
};


#endif