#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* ren, int screenwidth, int screenheight)
{
    startButton.InitButton(ren);
    startButton.srect.y = 0;
    startButton.drect.x = screenwidth / 2 - startButton.drect.w / 2;
    startButton.drect.y = screenheight / 2 -100- startButton.drect.h / 2;;

    exitButton.InitButton(ren);
    exitButton.srect.y = 700;
    exitButton.drect.x = screenwidth / 2 - exitButton.drect.w / 2;
    exitButton.drect.y = screenheight/2 - exitButton.drect.h / 2;

}

void MainMenu::updateButtons()
{
    if (Start == false) {
    startButton.update();
    exitButton.update();
    }
}

void MainMenu::drawButtons(SDL_Renderer* ren)
{
    if (Start == false) {
        startButton.draw(ren);
        exitButton.draw(ren);
    }
}

