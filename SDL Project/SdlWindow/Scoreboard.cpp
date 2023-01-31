#ifndef SCOREBOARD_CPP
#define SCOREBOARD_CPP

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Scoreboard.h"
#include <string>

Scoreboard::Scoreboard(const std::string font_path, int font_size, const std::string message, const SDL_Color& color, SDL_Renderer* renderer) {
	texture = loadFont(font_path, font_size, message, color, renderer);
	SDL_QueryTexture(texture, nullptr, nullptr, &text_rectangle.w, &text_rectangle.h);
}

Scoreboard::Scoreboard(int points) {
	this->points = points;
}

void Scoreboard::setPoints(int x, const std::string font_path, SDL_Renderer* renderer) {
	this->points = x;
	this->convertIntoString = std::to_string(this->points);
	texture = loadFont(font_path, 24, convertIntoString, { 255, 0, 0, 255 }, renderer);
	SDL_QueryTexture(texture, nullptr, nullptr, &text_rectangle.w, &text_rectangle.h);
	std::cout << "\nPoints are at: " << points << "\n";
}

void Scoreboard::display(int x, int y, SDL_Renderer* renderer) {
	text_rectangle.x = x;
	text_rectangle.y = y;
	SDL_RenderCopy(renderer, texture, NULL, &text_rectangle);
	SDL_RenderPresent(renderer);

}

SDL_Texture* Scoreboard::loadFont(const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	if (font == NULL) {
		std::cout << std::endl << "Could not load font";
		exit(1);
	}

	auto text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!text_surface) {
		std::cout << std::endl << "Failed to create surface";
	}

	auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (!text_texture) {
		std::cout << std::endl << "Failed to create texture";
	}

	SDL_FreeSurface(text_surface);
	//TTF_CloseFont(font);

	return text_texture;
}







#endif


