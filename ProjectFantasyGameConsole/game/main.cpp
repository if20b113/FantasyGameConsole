#include <stdio.h>
#include <iostream>
#include "Engine.h"
#include "FantasyGameEngine/FantasyGameEngine.hpp"

int main()
{
	FGE::test_lua();
	FGE::test_sdl();
	FGE::Engine eng;
	system("pause");
}