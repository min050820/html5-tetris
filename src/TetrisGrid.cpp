#include "TetrisGrid.h"

#include <algorithm>
#include <SDL.h>

#include "ProgramState.h"


TetrisGrid::TetrisGrid() {
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 10; j++)
			_grid[i][j] = TetriminoBlock::EMPTY;

	_fallingShape = TetriminoShape::INVALID;
	_fallingRotation = 0;
	_fallingY = 0;
	_fallingX = 0;
	_fallingTimer = 0;
	_fallingBlockedCount = 0;

	// 디버그용 코드
	_grid[0][0] = TetriminoBlock::I;
	_grid[0][1] = TetriminoBlock::I;
	_grid[0][2] = TetriminoBlock::I;
	_grid[0][3] = TetriminoBlock::I;

	_grid[1][3] = TetriminoBlock::Z;
	_grid[1][4] = TetriminoBlock::Z;
	_grid[0][4] = TetriminoBlock::Z;
	_grid[0][5] = TetriminoBlock::Z;

	_grid[2][5] = TetriminoBlock::S;
	_grid[1][5] = TetriminoBlock::S;
	_grid[1][6] = TetriminoBlock::S;
	_grid[0][6] = TetriminoBlock::S;

	_grid[2][1] = TetriminoBlock::T;
	_grid[1][0] = TetriminoBlock::T;
	_grid[1][1] = TetriminoBlock::T;
	_grid[1][2] = TetriminoBlock::T;

	_grid[1][8] = TetriminoBlock::O;
	_grid[1][9] = TetriminoBlock::O;
	_grid[0][8] = TetriminoBlock::O;
	_grid[0][9] = TetriminoBlock::O;
}

void TetrisGrid::render(ProgramState& state, SDL_Rect boundary) {
	SDL_SetRenderDrawBlendMode(state.renderer(), SDL_BLENDMODE_BLEND);
	SDL_Rect r;

	TetriminoBlock gridColor[20][10];
	bool isTransparent[20][10] = { false };

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			gridColor[i][j] = _grid[i][j];
		}
	}

	if (_fallingShape != TetriminoShape::INVALID) {
		// 고스트 블록 계산해줌
		int prevY = _fallingY;
		while (!_fallingBottomBlocked())
			_fallingY--;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				TetriminoBlock now = getTetriminoRasterShape(_fallingShape, _fallingRotation, i, j);
				// 조건 체크
				if (now == TetriminoBlock::EMPTY || i + _fallingY < 0 || i + _fallingY >= 20 || j + _fallingX < 0 || j + _fallingX >= 10)
					continue;
				gridColor[_fallingY + i][_fallingX + j] = now;
				isTransparent[_fallingY + i][_fallingX + j] = true;
			}
		}
		_fallingY = prevY;

		// 떨어지는 블록도 고려해줌
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				TetriminoBlock now = getTetriminoRasterShape(_fallingShape, _fallingRotation, i, j);
				// 조건 체크
				if (now == TetriminoBlock::EMPTY || i + _fallingY < 0 || i + _fallingY >= 20 || j + _fallingX < 0 || j + _fallingX >= 10)
					continue;
				gridColor[_fallingY + i][_fallingX + j] = now;
				isTransparent[_fallingY + i][_fallingX + j] = false;
			}
		}
	}

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
	float blockLen = contentXLen / 10.0f;

	// 내부 박스 그리기
	r = {
		(int)(boundary.x + padX),
		(int)(boundary.y + boundary.h - ((20) * blockLen)),
		(int)(blockLen * 10),
		(int)(blockLen * 20)
	};
	SDL_SetRenderDrawColor(state.renderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(state.renderer(), &r);


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

			// 현재 그려야 할 블록
			TetriminoBlock renderBlock = gridColor[i][j];

			int alpha = isTransparent[i][j] ? 127 : 255;

			switch (renderBlock) {
			case TetriminoBlock::I:
				SDL_SetRenderDrawColor(state.renderer(), 0, 240, 240, alpha);
				break;
			case TetriminoBlock::J:
				SDL_SetRenderDrawColor(state.renderer(), 0, 0, 240, alpha);
				break;
			case TetriminoBlock::L:
				SDL_SetRenderDrawColor(state.renderer(), 240, 160, 0, alpha);
				break;
			case TetriminoBlock::O:
				SDL_SetRenderDrawColor(state.renderer(), 240, 240, 0, alpha);
				break;
			case TetriminoBlock::S:
				SDL_SetRenderDrawColor(state.renderer(), 0, 240, 0, alpha);
				break;
			case TetriminoBlock::T:
				SDL_SetRenderDrawColor(state.renderer(), 160, 0, 240, alpha);
				break;
			case TetriminoBlock::Z:
				SDL_SetRenderDrawColor(state.renderer(), 240, 0, 0, alpha);
				break;
			default:
				SDL_SetRenderDrawColor(state.renderer(), 238, 238, 238, alpha);
				break;
			}
			SDL_RenderFillRect(state.renderer(), &r);
		}
	}
}

void TetrisGrid::update(ProgramState& state) {
	_updateFallingShape(state);
	_updateClearLine();
}

bool TetrisGrid::isNewFallingShapeRequired() {
	return _fallingShape == TetriminoShape::INVALID;
}

void TetrisGrid::pushNewFallingShape(TetriminoShape newShape) {
	_fallingShape = newShape;
	_fallingRotation = 0;
	_fallingY = 19;
	_fallingX = 4;
	_fallingTimer = 0;
	_fallingBlockedCount = 0;

	if (_fallingCheckOverlap())
		printf("Game ended!\n");
}

void TetrisGrid::doHardDrop() {
	// 구현 필요

	// 떨어진 뒤에는 타이머를 되돌림
	_fallingTimer = 0;
}

void TetrisGrid::doSoftDrop() {
	// 구현 필요

	// 떨어진 뒤에는 타이머를 되돌림
	_fallingTimer = 0;
}

void TetrisGrid::doRotateCW() {
	_tryRotateShape(true);
}

void TetrisGrid::doRotateCCW() {
	_tryRotateShape(false);
}

void TetrisGrid::doMoveLeft() {
	// 구현 필요
}

void TetrisGrid::doMoveRight() {
	// 구현 필요
}

void TetrisGrid::_tryRotateShape(bool isClockwise) {
	// 회전 시도할 때 움직임을 결정
	// 제자리에서 회전 시도한 뒤 실패하면 이 순서대로 블록을 움직인 뒤 회전을 시도함
	// 편의를 위해 제자리 회전 (0, 0)도 표에 넣음
	// 0번 축: 비교 순서
	// 1번 축: 각각 X, Y
	constexpr static int JLSTZ_ROTATION[5][2] = {
		{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}
	};

	// I모양 전용 회전 방식
	// 0번 축: 원래 회전
	// 1번 축: 비교 순서
	// 2번 축: 각각 X, Y
	constexpr static int I_ROTATION[4][5][2] = {
		{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
		{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
		{{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
		{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}
	};

	for (int i = 0; i < 5; i++) {
		if (_fallingShape != TetriminoShape::I) {
			int xDisp = JLSTZ_ROTATION[i][0] * (isClockwise ? 1 : -1);
			int yDisp = JLSTZ_ROTATION[i][1] * (isClockwise ? 1 : -1);
			if (_fallingRotateShape(xDisp, yDisp, isClockwise))
				return; // 회전이 성공하면 그대로 리턴
		}
		else {
			int xDisp, yDisp;
			if (isClockwise) {
				xDisp = I_ROTATION[_fallingRotation][i][0];
				yDisp = I_ROTATION[_fallingRotation][i][1];
			}
			else {
				xDisp = -I_ROTATION[(_fallingRotation + 3) % 4][i][0];
				yDisp = -I_ROTATION[(_fallingRotation + 3) % 4][i][1];
			}
			if (_fallingRotateShape(xDisp, yDisp, isClockwise))
				return;
		}
	}
}


void TetrisGrid::_updateFallingShape(ProgramState& state) {
	const float FALLING_DELAY = 0.756f;

	_fallingTimer += state.deltaTime;
	if (_fallingTimer < FALLING_DELAY)
		return;

	if (_fallingBottomBlocked()) {
		_fallingLockShape();
		return;
	}

	_fallingTimer -= FALLING_DELAY;

	_fallingY--;
}

int TetrisGrid::_updateClearLine() {
	int clearedLine = 0;

	for (int i = 0; i < 40; i++) {
		bool isFull = true;
		for (int j = 0; j < 10; j++)
			if (_grid[i][j] == TetriminoBlock::EMPTY)
				isFull = false;

		if (isFull) {
			for (int row = i + 1; row < 40; row++)
				for (int col = 0; col < 40; col++)
					_grid[row - 1][col] = _grid[row][col];
		}
	}

	return clearedLine;
}

bool TetrisGrid::_fallingRotateShape(int xDisp, int yDisp, bool isClockwise) {
	// 떨어지는 블록을 가로로 xDisp, 세로로 yDisp 만큼 움직이고 회전을 시도
	// 성공하면 true, 실패하면 false 리턴

	int rot = (isClockwise ? 1 : 3);
	int prevFallingRotation = _fallingRotation;

	// 상태를 (임시로) 적용
	_fallingX += xDisp;
	_fallingY += yDisp;
	_fallingRotation = (_fallingRotation + rot) % 4;

	// 겹치는지 확인 ("안" 겹치면 성공한거임)
	if (!_fallingCheckOverlap())
		return true;

	// 상태를 되돌리기
	_fallingX -= xDisp;
	_fallingY -= yDisp;
	_fallingRotation = prevFallingRotation;

	// 실패했다고 보고
	return false;
}

void TetrisGrid::_fallingLockShape() {
	// 떨어지는 조각을 그리드로 복사함

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 떨어지는 조각의 블록을 가져옴
			TetriminoBlock falling = getTetriminoRasterShape(_fallingShape, _fallingRotation, i, j);
			if (falling == TetriminoBlock::EMPTY)
				continue;

			_grid[_fallingY + i][_fallingX + j] = falling;
		}
	}

	_fallingShape = TetriminoShape::INVALID;
}

bool TetrisGrid::_fallingCheckOverlap() {
	// 떨어지는 조각과 게임판에 겹치는 블록이 있는지를 확인
	// 장 외에 위치한 블록이 있다면 무조건 겹치는 것으로 판정

	if (_fallingShape == TetriminoShape::INVALID)
		return false;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			TetriminoBlock block = getTetriminoRasterShape(_fallingShape, _fallingRotation, i, j);
			int gridY = i + _fallingY;
			int gridX = j + _fallingX;

			if (gridY < 0 || 40 <= gridY || gridX < 0 || 10 <= gridX) {
				if (block == TetriminoBlock::EMPTY)
					continue;
				return true;
			}

			if (_grid[gridY][gridX] != TetriminoBlock::EMPTY && block != TetriminoBlock::EMPTY)
				return true;
		}
	}
	return false;
}

bool TetrisGrid::_fallingBottomBlocked() {
	// 떨어지는 조각의 아래가 막혔는지를 검사
	// 조각을 아래로 한 칸 내린 상태에서 겹치는지를 확인하면 됨

	if (_fallingShape == TetriminoShape::INVALID)
		return false;

	// 이미 겹쳐있다면 막힌걸로 침
	if (_fallingCheckOverlap())
		return true;

	_fallingY--;

	bool didOverlap = _fallingCheckOverlap();

	_fallingY++;

	if (didOverlap)
		return true;
	else
		return false;
}