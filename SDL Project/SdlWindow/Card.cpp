#include "Card.h"

void Card::InitCard(SDL_Renderer* ren, int Id, int x, int y, int CardSize)
{

    static SDL_Texture* t = IMG_LoadTexture(ren, "resources/MemoryCardsTest.bmp");
    tex = t;
    drect.x = x;
    drect.y = y;

    CardId = Id;

    switch (CardId) {

    case 1:

        CardPicturex = 200;
        CardPicturey = 0;

        break;
    case 2:

        CardPicturex = 400;
        CardPicturey = 0;

        break;
    case 3:

        CardPicturex = 600;
        CardPicturey = 0;

        break;
    }


    srect.h = 200;
    srect.w = 200;
    srect.x = 0;
    srect.y = 0;
    drect.h = CardSize;
    drect.w = CardSize;

    soundtrack.load("resources/flipcard-91468.wav");
   

}

void Card::FlipCard() {
 
 if (isValid) {

        if (isFlipped == true) {
            // soundtrack.stop();
            soundtrack.play();
            isFlipped = false;
            srect.x = 0;
        }
        else
        {
            // soundtrack.stop();
            soundtrack.play();
            isFlipped = true;
            srect.x = CardPicturex;

        }
    } 
}



void Card::drawCard(SDL_Renderer* ren) {
    if (isValid) {
        SDL_RenderCopy(ren, tex, &srect, &drect);
    }
}
