#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "FantasyGameEngine/FantasyGameEngine.hpp"
#include "FantasyGameEngine/FileManagement.hpp"
#include "FantasyGameEngine/ScoreManagement.hpp"
#include "FantasyGameEngine/JobManagement.hpp"

using namespace FantasyGameEngine;

struct GameState {
	bool started = false;
	FGE_ImageHandle img;
	std::vector<glm::vec2> block_pos;
} game_state;

void init(const FGE_Renderer* renderer)
{
	game_state.img = load_image(renderer, "assets/button.png");

	for (int i = 0; i < 10; i++)
	{
		game_state.block_pos.push_back({ 30 + i * 100, 30 + i * 10 });
	}
}

void update(const FGE_Inputs* inputs)
{
	for (auto& pos : game_state.block_pos)
	{
		pos += glm::vec2(0, 10);
	}
}

void render(const FGE_Renderer* renderer, double delta)
{
	auto text = std::to_string(delta);

	render_text(renderer, { 5, 5 }, text.c_str());

	for (const auto& pos : game_state.block_pos)
	{
		FantasyGameEngine::render_image(renderer,
			pos,
			{ 50, 50 },
			game_state.img);
	}
}

int main()
{
	FantasyGameEngine::run(init, update, render, 0.5f * 1000);

	return 0;
}

/*
* 
* int async_add(int a, int b)
{
	return a + b;
}
int run_engine_tests()
{
	puts("TESTING BasicThreadPool ...");

	FantasyGameEngine::BasicThreadPool btp(5);

	auto work_result_1 = btp.enqueue(async_add, 4, 7);
	auto work_result_2 = btp.enqueue(async_add, 123, 12);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	printf("work result: %d, %d\n", 
		work_result_1.get(), 
		work_result_2.get());

	puts("\nTESTING LUA...");
	FantasyGameEngine::test_lua();
	
	puts("\nTESTING SDL...");
	printf("SDL TESTING RETURNED %d\n", 
		FantasyGameEngine::test_sdl());

	puts("\nTESTING FS...");
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

	return 0;
}
*/