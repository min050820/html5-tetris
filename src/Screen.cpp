#include "Screen.h"

#include <algorithm>

#include "ProgramState.h"


void Screen::update(ProgramState& state) {
	// 키보드 정보를 받아옴
	int keyCount;
	const uint8_t* currentKeys = SDL_GetKeyboardState(&keyCount);

	// 만약 키보드 상태 벡터의 크기가 이상하다면 상태를 리셋함
	if (keyState.size() != keyCount) {
		keyState.resize(keyCount);
		keyPressEvent.resize(keyCount);
		keyPressTime.resize(keyCount);

		std::fill(keyState.begin(), keyState.end(), false);
		std::fill(keyPressEvent.begin(), keyPressEvent.end(), false);
		std::fill(keyPressTime.begin(), keyPressTime.end(), 0.0f);
	}
	else {
		// 이전에 안 눌려있었고, 지금 눌려있다면 true로 설정
		for (int i = 0; i < keyCount; i++)
			keyPressEvent[i] = (!keyState[i]) && currentKeys[i];

		// 현 키보드 상태를 복사해옴
		for (int i = 0; i < keyCount; i++)
			keyState[i] = currentKeys[i];

		// 시간을 업데이트함
		for (int i = 0; i < keyCount; i++) {
			if (keyState[i])
				keyPressTime[i] += state.deltaTime;
			else
				keyPressTime[i] = 0.0f;
		}
	}
}