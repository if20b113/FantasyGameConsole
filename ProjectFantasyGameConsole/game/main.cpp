#include <stdio.h>
#include <iostream>
#include <memory>
#include "FGE/Engine.h"

int main()
{
	FGE::Engine engine;
//F:\Documents\GitHug\FantasyGameConsole\SDL Project\SdlWindow\resources

	engine.CreateObject(FGE::IMAGE, "button");
	engine.AttachTextureToObj("button", "D:\\fh\\FantasyGameConsole\\FantasyGameConsole\\ProjectFantasyGameConsole\\export\\assets\\button.png");
	engine.SetObjectActive("button");
	engine.RenderObject("button");
	system("pause");
}