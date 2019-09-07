// Created by Yun Yeomin <min050820@gmail.com>
// Licensed under GPLv3

#include <cstdio>
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// ProgramState 구조체
// 쓰는 이유: 웹 브라우저에서 작동시, 변수들을 포인터 하나로 가지고 있기 위함
struct ProgramState {
    bool quit = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

// 1 프레임당 한번 불리는 함수
void main_loop(ProgramState* state) {
    // 이벤트를 받을 변수
    SDL_Event event;

    // 아직 처리하지 않은 이벤트가 있는 동안에 이벤트를 받아서...
    while(SDL_PollEvent(&event)) {
        // 이벤트의 타입별로 switch 하고
        switch(event.type) {
            case SDL_QUIT:
                // 창 종료시 호출됨
                state->quit = true;
                break;
        }
    }

    // 색깔 지정 (#00000000)
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 0);
    // 스크린을 모두 지움
    SDL_RenderClear(state->renderer);

    // 그릴 색상 지정 (#C44040FF)
    SDL_SetRenderDrawColor(state->renderer, 196, 64, 64, 255);
    // 사각형 좌표 지정
    SDL_Rect rect;
    rect.w = 100;
    rect.h = 120;
    rect.x = 40;
    rect.y = 20;
    // 스크린에 그림
    SDL_RenderFillRect(state->renderer, &rect);

    // 화면을 업데이트함
    SDL_RenderPresent(state->renderer);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    // ProgramState 구조체 할당
    ProgramState *state = new ProgramState();

    // 창 생성
    state->window = SDL_CreateWindow(u8"A Tetris Clone",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            0);

    // 렌더러 생성
    state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

#ifdef __EMSCRIPTEN__
    // 웹 브라우저에서는 무한루프를 돌 수 없으므로 특수 함수를 이용함
    emscripten_set_main_loop_arg((void(*)(void*)) main_loop, state, -1, true);
#else
    // 일반 환경에서는 무한루프를 돌면서 함수를 호출
    while(!state->quit)
        main_loop(state);
#endif

    // 위에서 생성했던 리소스 정리
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);

    return 0;
}