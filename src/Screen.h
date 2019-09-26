#ifndef SCREEN_H_
#define SCREEN_H_


#include <SDL.h>

class ProgramState;

/**
@summary 화면에 표시되는 직사각형의 "스크린" 하나.

화면에 표시될 수 있는 화면 하나를 나타낸다.

화면에는 여러개의 스크린이 표시될 수 있지만 그 중 입력을 받는것은 단 하나이다.
메시지 창 같은걸 생각하면 편할듯.
*/
class Screen {
public:
	virtual ~Screen() {}
	virtual void update(ProgramState&) = 0;
	virtual void render(ProgramState&) = 0;
};


#endif