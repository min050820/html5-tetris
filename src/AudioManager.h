#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_


#include <atomic>
#include <SDL.h>


class AudioManager {
public:
	AudioManager();
	virtual ~AudioManager();
	void startPlayback();
	void stopPlayback();
	void audioCallback(float* stream, int len);

public:
	std::atomic<float> volume;

private:
	int currentPlayPosition = 0;
	SDL_AudioDeviceID _audioDevice;
	uint8_t *audioData;
	uint32_t audioDataLength;
};


#endif