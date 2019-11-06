#include "MainGameScreen.h"

#include <algorithm>

#include "ProgramState.h"


MainGameScreen::MainGameScreen(ProgramState& programState) {
	_audioManager.startPlayback();
}

MainGameScreen::~MainGameScreen() {
}

void MainGameScreen::update(ProgramState& state) {
	Screen::update(state);

	if (keyPressEvent[SDL_SCANCODE_SPACE])
		_tetrisGrid.doHardDrop();
	if (keyPressEvent[SDL_SCANCODE_UP] || keyPressEvent[SDL_SCANCODE_X])
		_tetrisGrid.doRotateCW();
	if (keyPressEvent[SDL_SCANCODE_LCTRL] || keyPressEvent[SDL_SCANCODE_Z])
		_tetrisGrid.doRotateCCW();
	if (keyPressEvent[SDL_SCANCODE_DOWN])
		_tetrisGrid.doSoftDrop();
	if (keyPressEvent[SDL_SCANCODE_LEFT])
		_tetrisGrid.doMoveLeft();
	if (keyPressEvent[SDL_SCANCODE_RIGHT])
		_tetrisGrid.doMoveRight();

	if (!keyState[SDL_SCANCODE_LEFT])
		_lastLeftRepeat = 0.0f;
	if (!keyState[SDL_SCANCODE_RIGHT])
		_lastRightRepeat = 0.0f;
	if (!keyState[SDL_SCANCODE_DOWN])
		_lastDownRepeat = 0.0f;

	if (keyPressTime[SDL_SCANCODE_LEFT] - _lastLeftRepeat > 0.5f) {
		_tetrisGrid.doMoveLeft();
		_lastLeftRepeat += 0.05f;
	}
	if (keyPressTime[SDL_SCANCODE_RIGHT] - _lastRightRepeat > 0.5f) {
		_tetrisGrid.doMoveRight();
		_lastRightRepeat += 0.05f;
	}
	if (keyPressTime[SDL_SCANCODE_DOWN] - _lastDownRepeat > 0.5f) {
		_tetrisGrid.doSoftDrop();
		_lastDownRepeat += 0.05f;
	}

	_tetrisGrid.update(state);

	if (_tetrisGrid.isNewFallingShapeRequired()) {
		_tetrisGrid.pushNewFallingShape(_tetriminoGenerator.next());
	}
}

void MainGameScreen::render(ProgramState& state) {
	int minLength = std::min(state.width(), state.height());
	int screenLength = minLength - 50;

	int screenY = (state.height() - screenLength) / 2;
	int screenX = (state.width() - screenLength) / 2;

	SDL_Rect r = { screenX, screenY, screenLength, screenLength };
	SDL_SetRenderDrawColor(state.renderer(), 32, 32, 32, 255);
	SDL_RenderFillRect(state.renderer(), &r);

	_tetrisGrid.render(state, {screenX + 16, screenY + 16, screenLength - 32, screenLength - 32});
}