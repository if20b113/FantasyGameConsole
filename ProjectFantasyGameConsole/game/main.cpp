#include <stdio.h>
#include <iostream>
#include <memory>
#include "FGE/Engine.h"

int main()
{
	FGE::Engine engine;
//F:\Documents\GitHug\FantasyGameConsole\SDL Project\SdlWindow\resources

	engine.CreateObject(FGE::IMAGE, "button");
	//engine.AttachTextureToObj("button", "F:\\Documents\\GitHug\\FantasyGameConsole\\SDL Project\\SdlWindow\\resources\\button.png");
	//engine.RenderObject("button");
	system("pause");
}