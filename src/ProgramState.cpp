#include "ProgramState.h"

#include <memory>

#include <SDL.h>

#include "MainGameScreen.h"


// ProgramState의 생성자
ProgramState::ProgramState() : _height(600), _width(800) {
	// 창 생성
	_window = SDL_CreateWindow(u8"A Tetris Clone",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_width, _height,
		SDL_WINDOW_RESIZABLE);


	// 렌더러 생성
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// 초기 화면 구성
	_screen = std::make_shared<MainGameScreen>(*this);
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

	// 스크린을 업데이트
	_screen->update(*this);
	
	// 렌더링을 함 (=화면을 그림)
	_render();
}

// 이벤트를 처리하는 함수
void ProgramState::_processEvent() {
	// 이벤트를 받을 변수
	SDL_Event event;

	// 아직 처리하지 않은 이벤트가 있는 동안에 이벤트를 받아서...
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		// 창이 닫히기를 원함
		case SDL_QUIT:
			flagQuit = true;
			break;

		// 창 관련 이벤트 발생
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			// 어떠한 이유든 간에, 창 크기가 바뀜
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				_width = event.window.data1;
				_height = event.window.data2;
				break;
			}
		}
	}
}

// 렌더링을 하는 함수
void ProgramState::_render() {
	// 색깔 지정 (#00000000)
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	// 스크린을 모두 지움
	SDL_RenderClear(_renderer);

	// 스크린을 화면에 그림
	_screen->render(*this);

	// 화면을 업데이트함
	SDL_RenderPresent(_renderer);
}