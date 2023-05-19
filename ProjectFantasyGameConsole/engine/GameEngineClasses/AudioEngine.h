#pragma once
#include "Audio.h"

class AudioEngine
{
public:
	Audio audio{};
	void LoadAudio(const char* filename);
	void PlayAudio();
	void StopAudio();
};