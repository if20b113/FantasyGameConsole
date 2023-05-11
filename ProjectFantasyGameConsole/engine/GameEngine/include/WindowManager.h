#pragma once
#include <sdl.h>

namespace FGE
{
	struct WindowConfig
	{
		int x = SDL_WINDOWPOS_CENTERED;
		int y = SDL_WINDOWPOS_CENTERED;
		int w = 600;
		int h = 400;
		Uint32 flags = SDL_WINDOW_SHOWN & SDL_WINDOW_RESIZABLE;
	};

	class Window // Creates SDL Window
	{
	private:
		SDL_Window* m_window;
		WindowConfig m_cfg;
		//bool CreateWindow();
	public:
		Window(); // Using default configuration
		Window(WindowConfig const cfg);
	};
}
