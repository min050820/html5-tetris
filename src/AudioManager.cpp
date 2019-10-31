#include "AudioManager.h"

#include <stdio.h>
#include <cmath>

#include <SDL.h>


static void sdl_audio_callback(void* udata, uint8_t* stream, int len) {
	AudioManager* manager = (AudioManager*)udata;
	float* actualStream = (float*) stream;
	int actualLength = len / sizeof(float);

	manager->audioCallback(actualStream, actualLength);
}


AudioManager::AudioManager() : volume(0.25f) {
	SDL_AudioSpec wanted, obtained;

	wanted.freq = 48000;
	wanted.format = AUDIO_F32;
	wanted.channels = 1;    // 1 = 모노, 2 = 스트레오
	wanted.samples = 2048;  // 랙걸릴 때를 대비한 버퍼. samples / channels / freq 초만큼의 딜레이 발생
	wanted.callback = sdl_audio_callback;
	wanted.userdata = this; // 콜백 함수가 이 오브젝트를 받도록 함.

	_audioDevice = SDL_OpenAudioDevice(nullptr, 0, &wanted, &obtained, 0);
	if (_audioDevice == 0)
		printf("AudioManager: Unable to open audio!\n");
}

AudioManager::~AudioManager() {
	SDL_CloseAudioDevice(_audioDevice);
}

void AudioManager::startPlayback() {
	SDL_PauseAudioDevice(_audioDevice, 0);
}

void AudioManager::stopPlayback() {
	SDL_PauseAudioDevice(_audioDevice, 1);
}


// Microsoft Visual Studio 일 경우, 오디오 랙을 방지하기 위해 최적화를 켬
#ifdef _MSC_VER
#pragma optimize("t", on)
#endif

void AudioManager::audioCallback(float* stream, int len) {
	for (int i = 0; i < len; i++) {
		float val = sin(i * M_PI * 2 / 128);
		stream[i] = val;
	}

	// 볼륨 조절
	const float nowVolume = volume;
	for (int i = 0; i < len; i++)
		stream[i] *= nowVolume;
}