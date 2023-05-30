#pragma once
#include <SDL_mixer.h>

class SoundEngine {
public:
    SoundEngine();
    ~SoundEngine();
    void Initialize();
    void LoadSounds();
    void PlaySounds();
    void Shutdown();

private:
    Mix_Chunk* soundEffect;
    Mix_Music* music;
};
