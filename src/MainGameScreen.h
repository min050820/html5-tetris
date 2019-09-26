#ifndef MAIN_GAME_SCREEN_H_
#define MAIN_GAME_SCREEN_H_


#include "Screen.h"

class MainGameScreen : public Screen {
public:
	MainGameScreen(ProgramState&) {}
	virtual ~MainGameScreen() {}

	virtual void update(ProgramState&);
	virtual void render(ProgramState&);
};


#endif