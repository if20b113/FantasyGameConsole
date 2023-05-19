#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>

class InputEngine {
public:
    InputEngine();
    bool isKeyPressed(SDL_Keycode key);
    bool isMouseButtonPressed(Uint8 button);
    bool quitRequested();

    int getMouseX();
    int getMouseY();

private:
    bool quit_requested_;
};

#endif // INPUT_HANDLER_H
