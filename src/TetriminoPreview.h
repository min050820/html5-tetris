#ifndef TETRIMINO_PREVIEW_H_
#define TETRIMINO_PREVIEW_H_


#include <SDL.h>

class ProgramState;
class TetriminoGenerator;


class TetriminoPreview {
public:
	void render(ProgramState& state, SDL_Rect boundary);
	void setTetriminoGenerator(TetriminoGenerator* newGenerator);

private:
	TetriminoGenerator* _generator = nullptr;
};


#endif