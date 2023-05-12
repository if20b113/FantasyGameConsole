#include <stdio.h>
#include <iostream>

#include "FantasyGameEngine/FantasyGameEngine.hpp"
#include "FantasyGameEngine/FileManager.hpp"

int main()
{
	FantasyGameEngine::test_lua();
	FantasyGameEngine::test_sdl();

	puts("reading file ...");
	auto test_file = FantasyGameEngine::read_text_from_file("assets/scripts/test.lua");
	std::cout << test_file << std::endl;

	FantasyGameEngine::write_text_to_file("test.txt", test_file);
}