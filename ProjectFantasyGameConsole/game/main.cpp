#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "FantasyGameEngine/FantasyGameEngine.hpp"
#include "FantasyGameEngine/FileManagement.hpp"
#include "FantasyGameEngine/ScoreManagement.hpp"
#include "FantasyGameEngine/JobManagement.hpp"

int main()
{
	FantasyGameEngine::test_lua();
	FantasyGameEngine::test_sdl();

	puts("reading file ...");
	auto test_file = FantasyGameEngine::read_text_from_file("assets/scripts/test.lua");
	std::cout << test_file << std::endl;

	FantasyGameEngine::score_system_init();

	FantasyGameEngine::update_score("adam", 10);
	FantasyGameEngine::update_score("florian", 15);
	FantasyGameEngine::update_score("faisalhanbali", 20); // Names longer than 8 chars can still be saved, without strict mode. Turning on strict mode is probably not worth it.

	for (const auto& e : FantasyGameEngine::get_scores())
		printf("got row from get_scores: %s, %d, %s\n",
			std::get<0>(e).c_str(),
			std::get<1>(e),
			std::get<2>(e).c_str());

	std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep to test if different timestamp is generated.

	FantasyGameEngine::update_score("adam", 25);

	puts("after update:");
	for (const auto& e : FantasyGameEngine::get_scores())
		printf("got row from get_scores: %s, %d, %s\n",
			std::get<0>(e).c_str(),
			std::get<1>(e),
			std::get<2>(e).c_str());

	FantasyGameEngine::write_text_to_file("test.txt", test_file);
}