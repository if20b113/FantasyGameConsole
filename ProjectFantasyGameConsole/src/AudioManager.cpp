#include <SDL.h>
#include <SDL_audio.h>

class AudioManager {
public:
    AudioManager(const char* audioFileName) : audioBuffer(nullptr), audioLength(0) {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            SDL_Log("SDL initialization failed: %s", SDL_GetError());
            return;
        }

        // Set up the audio specifications
        audioSpec.freq = SAMPLE_RATE;
        audioSpec.format = AUDIO_FORMAT;
        audioSpec.channels = CHANNELS;
        audioSpec.samples = BUFFER_SIZE;
        audioSpec.callback = AudioCallback;
        audioSpec.userdata = this;

        // Open the audio device
        audioDevice = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
        if (audioDevice == 0) {
            SDL_Log("Failed to open audio device: %s", SDL_GetError());
            SDL_Quit();
            return;
        }

        // Load the audio file
        if (SDL_LoadWAV(audioFileName, &loadedSpec, &audioBuffer, &audioLength) == nullptr) {
            SDL_Log("Failed to load audio file: %s", SDL_GetError());
            SDL_CloseAudioDevice(audioDevice);
            SDL_Quit();
            return;
        }
    }

    ~AudioManager() {
        // Clean up
        SDL_CloseAudioDevice(audioDevice);
        if (audioBuffer) {
            SDL_FreeWAV(audioBuffer);
        }
        SDL_Quit();
    }

    void Play() {
        // Start audio playback
        SDL_PauseAudioDevice(audioDevice, 0);

        // Wait for audio to finish playing
        while (audioLength > 0) {
            SDL_Delay(100);
        }
    }

private:
    static const int SAMPLE_RATE = 44100;
    static const Uint16 AUDIO_FORMAT = AUDIO_S16SYS;
    static const int CHANNELS = 2;
    static const int BUFFER_SIZE = 4096;

    SDL_AudioSpec audioSpec;
    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec loadedSpec;

    // Audio data and its length
    Uint8* audioBuffer;
    Uint32 audioLength;

    static void AudioCallback(void* userdata, Uint8* stream, int len) {
        AudioManager* audioManager = static_cast<AudioManager*>(userdata);

        if (audioManager->audioLength == 0) {
            return;
        }

        len = (len > audioManager->audioLength) ? audioManager->audioLength : len;

        SDL_memcpy(stream, audioManager->audioBuffer, len);

        audioManager->audioBuffer += len;
        audioManager->audioLength -= len;
    }
};
