#include "TetrisGrid.h"

#include <algorithm>
#include <SDL.h>

#include "ProgramState.h"


TetrisGrid::TetrisGrid() {
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 10; j++)
			_grid[i][j] = TetriminoBlock::EMPTY;

	_fallingNewShapeRequired = false;
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

			// 현재 그려야 할 블록
			TetriminoBlock renderBlock = _grid[i][j];

			// 떨어지는 블록도 고려해줌
			// (구현 필요)

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
				SDL_SetRenderDrawColor(state.renderer(), 238, 238, 238, 255);
				break;
			}
			SDL_RenderFillRect(state.renderer(), &r);
		}
	}
}

void TetrisGrid::update(ProgramState& state) {
	// 키 입력 받음
	const uint8_t *keystate = SDL_GetKeyboardState(nullptr);
	bool nowKeyRotateClockwise = keystate[SDL_SCANCODE_X] || keystate[SDL_SCANCODE_UP];
	bool nowKeyRotateCounterClockwise = keystate[SDL_SCANCODE_LCTRL] || keystate[SDL_SCANCODE_Z];
	bool nowKeyLeft = keystate[SDL_SCANCODE_LEFT];
	bool nowKeyRight = keystate[SDL_SCANCODE_RIGHT];
	bool nowKeyDown = keystate[SDL_SCANCODE_DOWN];

	// 방금 전까지는 안 눌려 있었는데 눌려 있어야 입력으로 침
	// 사이드 퀘스트: 꾹 누르면 연속으로 움직이는 것을 구현해 보자
	if (!_keyRotateClockwise && nowKeyRotateClockwise) {
		int prevRotation = _fallingRotation;
		_fallingRotation = (_fallingRotation + 1) % 4;
		if (_fallingCheckOverlap()) {
			_fallingX++;
			if (_fallingCheckOverlap()) {
				_fallingX -= 2;
				if (_fallingCheckOverlap()) {
					_fallingX++;
					_fallingRotation = prevRotation;
				}
			}
		}
	}
	if (!_keyRotateCounterClockwise && nowKeyRotateCounterClockwise) {
		int prevRotation = _fallingRotation;
		_fallingRotation = (_fallingRotation + 3) % 4;
		if (_fallingCheckOverlap()) {
			_fallingX++;
			if (_fallingCheckOverlap()) {
				_fallingX -= 2;
				if (_fallingCheckOverlap()) {
					_fallingX++;
					_fallingRotation = prevRotation;
				}
			}
		}
	}
	if (!_keyLeft && nowKeyLeft) {
		_fallingX--;
		if (_fallingCheckOverlap())
			_fallingX++;
	}
	if (!_keyRight && nowKeyRight) {
		_fallingX++;
		if (_fallingCheckOverlap())
			_fallingX--;
	}
	if (!_keyDown && nowKeyDown && _fallingShape != TetriminoShape::INVALID) {
		_fallingY--;
		_fallingTimer = 0;
	}

	// 입력값을 저장
	_keyRotateClockwise = nowKeyRotateClockwise;
	_keyRotateCounterClockwise = nowKeyRotateCounterClockwise;
	_keyLeft = nowKeyLeft;
	_keyRight = nowKeyRight;
	_keyDown = nowKeyDown;

	_updateFallingShape(state);
}

bool TetrisGrid::isNewFallingShapeRequired() {
	return _fallingNewShapeRequired;
}

void TetrisGrid::pushNewFallingShape(TetriminoShape newShape) {
	_fallingNewShapeRequired = false;
	_fallingShape = newShape;
	_fallingRotation = 3;
	_fallingY = 18;
	_fallingX = 4;
	_fallingTimer = 0;
	_fallingBlockedCount = 0;
}


void TetrisGrid::_updateFallingShape(ProgramState& state) {
	if (_fallingShape == TetriminoShape::INVALID) {
		_fallingNewShapeRequired = true;
		return;
	}

	if (_fallingBottomBlocked()) {
		_fallingLockShape();
		return;
	}

	const float FALLING_DELAY = 1.0f;

	_fallingTimer += state.deltaTime;
	if (_fallingTimer < FALLING_DELAY)
		return;

	_fallingTimer -= FALLING_DELAY;

	_fallingY--;
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
	// (구현 필요)
	return false;
}

bool TetrisGrid::_fallingBottomBlocked() {
	// 떨어지는 조각의 아래가 막혔는지를 검사
	// 조각을 아래로 한 칸 내린 상태에서 겹치는지를 확인하면 됨

	if (_fallingShape == TetriminoShape::INVALID)
		return false;

	_fallingY--;

	bool didOverlap = _fallingCheckOverlap();

	_fallingY++;

	if (didOverlap)
		return true;
	else
		return false;
}