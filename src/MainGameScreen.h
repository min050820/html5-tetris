#ifndef MAIN_GAME_SCREEN_H_
#define MAIN_GAME_SCREEN_H_


#include "Screen.h"
#include "AudioManager.h"
#include "TetrisGrid.h"
#include "TetriminoGenerator.h"


class MainGameScreen : public Screen {
public:
	MainGameScreen(ProgramState& programState);
	virtual ~MainGameScreen();

	virtual void update(ProgramState&);
	virtual void render(ProgramState&);

private:
	AudioManager _audioManager;
	TetrisGrid _tetrisGrid;
	TetriminoGenerator _tetriminoGenerator;
};


#endif