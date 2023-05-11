#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <list>

typedef enum SearchTerm
{
	PER_TITLE = 0,
	PER_PTR = 1

};

struct WindowStorage
{
	const char* winTitle;
	SDL_Window* winPtr;
	SDL_Renderer* winRend;

	TTF_Font* s_Font;
	SDL_Surface* s_Surface;
	SDL_Texture* s_Texture;
	
	WindowStorage()
	{
		winTitle	= NULL;
		winPtr		= NULL;
		winRend		= NULL;
		s_Font		= NULL;
		s_Surface	= NULL;
		s_Texture	= NULL;
	}
};

struct WindowConfig
{
	// Default config. Load in values from outside (to do)
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int w = 600;
	int h = 400;
	Uint32 flags = SDL_WINDOW_SHOWN & SDL_WINDOW_RESIZABLE;
};

class WindowManager // Use as global variable
{
private:
	std::list<WindowStorage> m_windows; // Stores all windows
	WindowConfig m_cfg;
	const std::string m_fontPath = "resources/tahoma.ttf"; // Default font
	//const std::string m_fontPath = "resources/PublicPixel.ttf"; // Default font
	const int m_defaultFontSize = 72;
	SDL_Color const m_defaultColor{ 255,255,255 }; // White
	TTF_Font* loadFont(const std::string& font_path, int font_size);
	void unloadFont(SDL_Renderer* renderer);

public:
	WindowManager();
	~WindowManager();
	SDL_Window* createWindow(const char* title); // Create window, set into storage
	WindowStorage* getWindow(void* term, SearchTerm perTerm);
	void RenderWindow(SDL_Window* const window);
	void RenderWindow(SDL_Renderer* const renderer);
	void displayText(const int x, const int y, const std::string& text, const WindowStorage& storage); // this -> loadFont

};

/*
Use example:
	const char* winName = "MyWindow";
	WindowStorage store = manager.getWindow(manager.createWindow(winName), PER_PTR);
	manager.RenderWindow(store.winRend);
*/

#endif


