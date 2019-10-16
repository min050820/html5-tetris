#include "TetrisGrid.h"

#include <SDL.h>

#include "ProgramState.h"


TetrisGrid::TetrisGrid() {
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 10; j++)
			grid[i][j] = Tetrimino::EMPTY;

	// 디버그용 코드
	srand(1234567890);
	for (int i = 4; i < 40; i++)
		for (int j = 0; j < 10; j++)
			grid[i][j] = (Tetrimino)(rand() % 8);

	grid[0][0] = Tetrimino::I;
	grid[0][1] = Tetrimino::I;
	grid[0][2] = Tetrimino::I;
	grid[0][3] = Tetrimino::I;

	grid[1][3] = Tetrimino::Z;
	grid[1][4] = Tetrimino::Z;
	grid[0][4] = Tetrimino::Z;
	grid[0][5] = Tetrimino::Z;

	grid[2][5] = Tetrimino::S;
	grid[1][5] = Tetrimino::S;
	grid[1][6] = Tetrimino::S;
	grid[0][6] = Tetrimino::S;

	grid[2][1] = Tetrimino::T;
	grid[1][0] = Tetrimino::T;
	grid[1][1] = Tetrimino::T;
	grid[1][2] = Tetrimino::T;

	grid[1][8] = Tetrimino::O;
	grid[1][9] = Tetrimino::O;
	grid[0][8] = Tetrimino::O;
	grid[0][9] = Tetrimino::O;
}

void TetrisGrid::render(ProgramState& state, SDL_Rect boundary) {
	SDL_Rect r;

	// 외부 박스 크기 계산
	// padY는 위쪽에만 적용
	// padX는 양쪽에 적용
	int padY = boundary.h / 10;
	int contentYLen = boundary.h - padY;
	// 박스의 가로 크기는 세로 크기의 0.5배
	int contentXLen = (boundary.h - padY) / 2;
	// 가로 크기에 맞는 세로 크기 계산
	int padX = (boundary.w - contentXLen) / 2;

	float blockLen = contentXLen / 10.0f;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			// [i][j]칸의 좌표 찾기
			// 너비, 높이는 float->int 변환으로 인해 건너뛰는 픽셀이 없도록 1을 더함
			// 나중에는 아예 렌더링을 다르게 할 예정
			r = {
				(int)(boundary.x + padX + j * blockLen),
				(int)(boundary.y + boundary.h - ((i + 1) * blockLen)),
				(int)blockLen + 1,
				(int)blockLen + 1
			};

			
			SDL_SetRenderDrawColor(state.renderer(), 238, 238, 238, 255);
			SDL_RenderFillRect(state.renderer(), &r);
		}
	}
}

void TetrisGrid::update(ProgramState& state) {
	// key input
}