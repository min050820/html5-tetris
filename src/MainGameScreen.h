#ifndef MAIN_GAME_SCREEN_H_
#define MAIN_GAME_SCREEN_H_


#include "Screen.h"
#include "TetrisGrid.h"


class MainGameScreen : public Screen {
	TetrisGrid tetrisGrid;

public:
	MainGameScreen(ProgramState&) {}
	virtual ~MainGameScreen() {}

	virtual void update(ProgramState&);
	virtual void render(ProgramState&);
};


#endif