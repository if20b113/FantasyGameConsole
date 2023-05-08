#include "InputEngine.h"

InputEngine::InputEngine() : quit_requested_(false) {}

bool InputEngine::isKeyPressed(SDL_Keycode key) {
    // Check if the specified key is currently pressed
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_GetScancodeFromKey(key)]) {
        return true;
    }
    return false;
}

bool InputEngine::isMouseButtonPressed(Uint8 button) {
    // Check if the specified mouse button is currently pressed
    const Uint32 state = SDL_GetMouseState(nullptr, nullptr);
    if (state & SDL_BUTTON(button)) {
        return true;
    }
    return false;
}

bool InputEngine::quitRequested() {
    // Check if the user has requested to quit the application
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit_requested_ = true;
        }
    }
    return quit_requested_;
}

int InputEngine::getMouseX() {
    // Get the current x position of the mouse
    int x;
    SDL_GetMouseState(&x, nullptr);
    return x;
}

int InputEngine::getMouseY() {
    // Get the current y position of the mouse
    int y;
    SDL_GetMouseState(nullptr, &y);
    return y;
}
