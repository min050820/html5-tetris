#include "ProgramState.h"

#include <SDL.h>


// ProgramState의 생성자
ProgramState::ProgramState() {
	// 창 생성
	_window = SDL_CreateWindow(u8"A Tetris Clone",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_ALLOW_HIGHDPI);

	// 렌더러 생성
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

// ProgramState의 소멸자 (객체가 삭제될 때 불림)
ProgramState::~ProgramState() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

// 메인 루프: 한 프레임당 한 번 불리는 함수
void ProgramState::mainLoop() {
	// 이벤트를 처리함
	_processEvent();

	// 만약 나가야 한다면 나감
	if (flagQuit)
		return;
	
	// 렌더링을 함 (=화면을 그림)
	_render();
}

// 이벤트를 처리하는 함수
void ProgramState::_processEvent() {
	// 이벤트를 받을 변수
	SDL_Event event;

	// 아직 처리하지 않은 이벤트가 있는 동안에 이벤트를 받아서...
	while (SDL_PollEvent(&event)) {
		// 이벤트의 타입별로 switch 하고
		switch (event.type) {
		case SDL_QUIT:
			// 창 종료시 호출됨
			flagQuit = true;
			break;
		}
	}
}

// 렌더링을 하는 함수
void ProgramState::_render() {
	// 색깔 지정 (#00000000)
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	// 스크린을 모두 지움
	SDL_RenderClear(_renderer);

	// 그릴 색상 지정 (#C44040FF)
	SDL_SetRenderDrawColor(_renderer, 196, 64, 64, 255);
	// 사각형 좌표 지정
	SDL_Rect rect;
	rect.w = 100;
	rect.h = 120;
	rect.x = 40;
	rect.y = 20;
	// 스크린에 그림
	SDL_RenderFillRect(_renderer, &rect);

	// 화면을 업데이트함
	SDL_RenderPresent(_renderer);
}