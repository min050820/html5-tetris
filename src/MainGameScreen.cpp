#include "MainGameScreen.h"

#include <algorithm>

#include "ProgramState.h"


void MainGameScreen::update(ProgramState& state) {
	tetrisGrid.update(state);

	if (tetrisGrid.isNewFallingShapeRequired()) {
		tetrisGrid.pushNewFallingShape(tetriminoGenerator.next());
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

	tetrisGrid.render(state, {screenX + 16, screenY + 16, screenLength - 32, screenLength - 32});
}