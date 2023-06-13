#include "AudioEngine.h"

void AudioEngine::LoadAudio(const char* filename)
{
	audio.load(filename);
}

void AudioEngine::PlayAudio()
{
	audio.play();
}

void AudioEngine::StopAudio()
{
	audio.~Audio();

}