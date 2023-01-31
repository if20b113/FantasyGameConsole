#include "KeyboardController.h"

KeyboardController::KeyboardController(int GridRows, int GridColumns){

    Gridrows = GridRows-1;
    Gridcolumns = GridColumns-1;
}

/*void KeyboardController::Keyboardinput(SDL_Event* event) {

    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            SDL_Log("Left Arrow pressed\n");
            break;
        case SDLK_RIGHT:
            SDL_Log("Right Arrow pressed\n");
            break;
        case SDLK_UP:
            SDL_Log("UP Arrow pressed\n");
            break;
        case SDLK_DOWN:
            SDL_Log("DOWN Arrow pressed\n");
            break;
        case SDLK_w:
            SDL_Log("W Key pressed\n");
            break;
        case SDLK_a:
            SDL_Log("A Key pressed\n");
            break;
        case SDLK_s:
            SDL_Log("S Key pressed\n");
            break;
        case SDLK_d:
            SDL_Log("D Key pressed\n");
            break;
        default:
            break;
        }

        break;

    case SDL_KEYUP:
        switch (event->key.keysym.sym) {
            switch (event->key.keysym.sym) {
            case SDLK_LEFT:
                SDL_Log("Left Arrow released\n");
                break;
            case SDLK_RIGHT:
                SDL_Log("Right Arrow released\n");
                break;
            case SDLK_UP:
                SDL_Log("UP Arrow released\n");
                break;
            case SDLK_DOWN:
                SDL_Log("DOWN Arrow released\n");
                break;
            case SDLK_w:
                SDL_Log("W Key released\n");
                break;
            case SDLK_a:
                SDL_Log("A Key released\n");
                break;
            case SDLK_s:
                SDL_Log("S Key released\n");
                break;
            case SDLK_d:
                SDL_Log("D Key released\n");
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}*/

void KeyboardController::Testinput(const Uint8* keys) {
    
    if (keys[SDL_SCANCODE_S]) {

        curcolum++;
    }

    if (keys[SDL_SCANCODE_W]) {
        curcolum--;
    }

    if (keys[SDL_SCANCODE_A]) {
        currow--;
    }

    if (keys[SDL_SCANCODE_D]) {
        currow++;
    }

    if (curcolum < 0) {

        curcolum = Gridcolumns;

    }

    if (curcolum > Gridcolumns) {

        curcolum = 0;
    }

    if (currow < 0) {

        currow = Gridrows;

    }

    if (currow > Gridcolumns) {

        currow = 0;
    }

    SDL_Log("CurColum: %d\n", curcolum);
    SDL_Log("CurRow: %d\n", currow);
}

