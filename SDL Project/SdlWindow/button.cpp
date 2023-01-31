#include "button.h"


void Button::InitButton(SDL_Renderer* ren) {

    static SDL_Texture* t = IMG_LoadTexture(ren, "resources/button.png");
    tex = t;

    srect.h = 100;
    srect.w = 400;
    srect.x = 0;

    drect.h = 75;
    drect.w = 300;

}



void Button::update() {

   // SDL_Log("%d %d Test", drect.x,drect.y);

    if (isSelected == true) {
        //SDL_Log("intersects");
        srect.x = 400;
    }
    else {
        //SDL_Log("doesnt intersect");
        srect.x = 0;
    }
}

void Button::draw(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, tex, &srect, &drect);
}