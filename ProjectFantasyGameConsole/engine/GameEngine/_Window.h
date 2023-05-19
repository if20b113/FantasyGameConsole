#pragma once

#include "SDL.h"

#include "Window.h"

namespace FGE
{
	class Window // Creates SDL Window
	{
	private:
		SDL_Window* m_window;
		WindowConfig m_cfg;
        void parse_flags();
		//bool CreateWindow();
	public:
		Window(); // Using default configuration
		Window(WindowConfig const cfg);
	};
}
