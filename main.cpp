// Created by Yun Yeomin <min050820@gmail.com>
// Licensed under GPLv3

#include <cstdio>
#include <SDL.h>

#include <memory>

#include "src/ProgramState.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// 1 프레임당 한 번 불리는 함수
void main_loop(ProgramState* state) {
	state->mainLoop();
}

#include "src/Tetrimino.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    // ProgramState 클래스 할당
	std::unique_ptr<ProgramState> state = std::make_unique<ProgramState>();

#ifdef __EMSCRIPTEN__
    // 웹 브라우저에서는 무한루프를 돌 수 없으므로 특수 함수를 이용함
    emscripten_set_main_loop_arg((void(*)(void*)) main_loop, state.get(), -1, true);
#else
    // 일반 환경에서는 무한루프를 돌면서 함수를 호출
    while(!state->flagQuit)
        main_loop(state.get());
#endif

	// 위에서 할당했던 ProgramState 클래스는 리턴하기 직전에 자동으로 삭제됨

    return 0;
}