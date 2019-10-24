#ifndef MAIN_GAME_SCREEN_H_
#define MAIN_GAME_SCREEN_H_


#include "Screen.h"
#include "TetrisGrid.h"
#include "TetriminoGenerator.h"


class MainGameScreen : public Screen {
public:
	MainGameScreen(ProgramState&) {}
	virtual ~MainGameScreen() {}

	virtual void update(ProgramState&);
	virtual void render(ProgramState&);

private:
	TetrisGrid tetrisGrid;
	TetriminoGenerator tetriminoGenerator;
};


#endif