#include <iostream>
#include <stdexcept>
#include <SDL.h>
#include <SDL_mixer.h>

class Engine {
public:
    Engine();
    ~Engine();
    void Initialize();
    void LoadSounds();
    void PlaySounds();
    void Shutdown();

private:
    Mix_Chunk* soundEffect;
    Mix_Music* music;
};

Engine::Engine() : soundEffect(nullptr), music(nullptr) {}

Engine::~Engine() {
    Shutdown();
}

void Engine::Initialize() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    // Initialize SDL Mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC) != 0) {
        // SDL Mixer initialization successful
    }
    else {
        throw std::runtime_error("Failed to initialize SDL Mixer: " + std::string(Mix_GetError()));
    }

    // Open audio device
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0) {
        throw std::runtime_error("Failed to open audio device: " + std::string(Mix_GetError()));
    }

    // Display available audio devices
    const int numDevices = SDL_GetNumAudioDevices(0);
    if (numDevices < 0) {
        throw std::runtime_error("Failed to retrieve audio device information: " + std::string(SDL_GetError()));
    }

    std::cout << "Available audio devices:" << std::endl;
    for (int i = 0; i < numDevices; ++i) {
        const char* deviceName = SDL_GetAudioDeviceName(i, 0);
        if (deviceName) {
            std::cout << i << ": " << deviceName << std::endl;
        }
    }
}

void Engine::LoadSounds() {
    soundEffect = Mix_LoadWAV("sound.wav");
    if (soundEffect == nullptr) {
        throw std::runtime_error("Failed to load sound effect: " + std::string(Mix_GetError()));
    }

    music = Mix_LoadMUS("music.mp3");
    if (music == nullptr) {
        throw std::runtime_error("Failed to load music: " + std::string(Mix_GetError()));
    }
    printf("Sound loaded\n");
    printf("Music loaded\n");
}

void Engine::PlaySounds() {
    //Mix_VolumeMusic(64); // Adjust the volume as desired (0-128)
    // Play sound effect
    Mix_PlayChannel(-1, soundEffect, -1);
    SDL_Delay(5000);
    Mix_PlayMusic(music, -1);
    SDL_Delay(5000);
}

void Engine::Shutdown() {
    Mix_FreeChunk(soundEffect);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}