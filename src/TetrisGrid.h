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
	void tryRotateShape(bool isClockwise);

private:
	void _updateFallingShape(ProgramState& state);
	int _updateClearLine();
	bool _fallingRotateShape(int xDisp, int yDisp, bool isClockwise);
	void _fallingLockShape();
	bool _fallingCheckOverlap();
	bool _fallingBottomBlocked();

private:
	// [0][0] = 왼쪽 아래
	TetriminoBlock _grid[40][10];

	bool _keyRotateClockwise = false;
	bool _keyRotateCounterClockwise = false;
	bool _keyLeft = false;
	bool _keyRight = false;
	bool _keyDown = false;
	bool _keyHardDrop = false;

	bool _fallingNewShapeRequired;
	TetriminoShape _fallingShape;
	int _fallingRotation, _fallingY, _fallingX;
	float _fallingTimer;
	int _fallingBlockedCount;
};


#endif