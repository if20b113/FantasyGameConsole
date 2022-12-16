#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <string>

class Scoreboard {
public:
	Scoreboard(const std::string font_path, int font_size, const std::string message, const SDL_Color& color, SDL_Renderer* renderer);

	Scoreboard(int points);

	void display(int x, int y, SDL_Renderer* renderer);

	static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color, SDL_Renderer* renderer);

	void setPoints(int x, const std::string font_path, SDL_Renderer* renderer);

private:
	SDL_Texture* texture = nullptr;
	mutable SDL_Rect text_rectangle{ 0, 0, 0, 0 };
	int points;
	std::string convertIntoString;		//convert points into string to pass as message




};


//#include "Scoreboard.cpp"

#endif