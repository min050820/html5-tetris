#include "TetriminoPreview.h"

#include "ProgramState.h"
#include "TetriminoGenerator.h"

#include <array>
#include <algorithm>
#include <cmath>
#include <SDL.h>


static float calcBlockSize(SDL_Rect boundary) {
	// 외부 박스 크기 계산
	// padY는 위쪽에만 적용
	// padX는 양쪽에 적용
	int padY = boundary.h / 10;
	int contentYLen = boundary.h - padY;
	// 박스의 가로 크기는 세로 크기의 0.5배
	int contentXLen = (boundary.h - padY) / 2;
	// 가로 크기에 맞는 세로 크기 계산
	int padX = (boundary.w - contentXLen) / 2;
	// 블록 하나 크기 계산
	return contentXLen / 10.0f;
}


void TetriminoPreview::render(ProgramState& state, SDL_Rect boundary) {
	SDL_Rect r;

	// 블록 하나의 크기 (블록 경계 계산용)
	float blockSizeF = calcBlockSize(boundary);

	// 블록 하나의 크기
	int blockSize = (int)blockSizeF;

	// 최소 높이
	int baseY = (int)(boundary.y + boundary.h - blockSizeF * 20);

	// 최소 X
	int baseX = boundary.x + boundary.w * 11 / 14;

	// 블록 미리보기 상태
	std::array<TetriminoShape, 3> peek;

	if (_generator != nullptr) {
		auto actual = _generator->peek();
		for (int i = 0; i < 3; i++)
			peek[i] = actual[i];
	}
	else {
		peek.fill(TetriminoShape::INVALID);
	}

	for (int i = 0; i < 3; i++) {
		// 모양 내의 y
		for (int j = 0; j < 4; j++) {
			// 모양 내의 x
			for (int k = 0; k < 4; k++) {
				TetriminoBlock renderBlock = TetriminoBlock::EMPTY;

				if (peek[i] != TetriminoShape::INVALID && j + 1 < 4) {
					renderBlock = getTetriminoRasterShape(peek[i], 0, j + 1, k);
				}

				r = { baseX + blockSize*k, baseY + (int)(blockSizeF*i*4.5f) + blockSize*j, blockSize, blockSize };
				switch (renderBlock) {
				case TetriminoBlock::I:
					SDL_SetRenderDrawColor(state.renderer(), 0, 240, 240, 255);
					break;
				case TetriminoBlock::J:
					SDL_SetRenderDrawColor(state.renderer(), 0, 0, 240, 255);
					break;
				case TetriminoBlock::L:
					SDL_SetRenderDrawColor(state.renderer(), 240, 160, 0, 255);
					break;
				case TetriminoBlock::O:
					SDL_SetRenderDrawColor(state.renderer(), 240, 240, 0, 255);
					break;
				case TetriminoBlock::S:
					SDL_SetRenderDrawColor(state.renderer(), 0, 240, 0, 255);
					break;
				case TetriminoBlock::T:
					SDL_SetRenderDrawColor(state.renderer(), 160, 0, 240, 255);
					break;
				case TetriminoBlock::Z:
					SDL_SetRenderDrawColor(state.renderer(), 240, 0, 0, 255);
					break;
				default:
					SDL_SetRenderDrawColor(state.renderer(), 196, 196, 196, 255);
					break;
				}
				SDL_RenderFillRect(state.renderer(), &r);
			}
		}
	}
}

void TetriminoPreview::setTetriminoGenerator(TetriminoGenerator* newGenerator) {
	_generator = newGenerator;
}