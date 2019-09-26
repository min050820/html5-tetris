#ifndef PROGRAM_STATE_H_
#define PROGRAM_STATE_H_


#include <memory>

class Screen;
struct SDL_Window;
struct SDL_Renderer;

// ProgramState 구조체
// 쓰는 이유: 웹 브라우저에서 작동시, 변수들을 포인터 하나로 가지고 있기 위함
class ProgramState {
public:
	ProgramState();
	~ProgramState();
	SDL_Window* window() { return _window; }
	SDL_Renderer* renderer() { return _renderer; }
	int width() { return _width; }
	int height() { return _height; }

	void mainLoop();

public:
	bool flagQuit = false;

private:
	void _processEvent();
	void _render();

private:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	int _width, _height;
	std::shared_ptr<Screen> _screen;
};


#endif