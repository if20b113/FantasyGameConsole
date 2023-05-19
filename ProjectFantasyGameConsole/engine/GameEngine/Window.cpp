#include <iostream>

#include "SDL.h"

#include "_Window.h"

namespace FGE
{
	void Window::parse_flags()
	{
		if (m_cfg.flags & FGE_WF_Centered)
		{
			m_cfg.x = SDL_WINDOWPOS_CENTERED;
			m_cfg.y = SDL_WINDOWPOS_CENTERED;
		}
	}

	Window::Window() // cfg is by default intialized with values
	{
		parse_flags();

		int default_flags = SDL_WINDOW_SHOWN & SDL_WINDOW_RESIZABLE;
		m_window = SDL_CreateWindow("Window", m_cfg.x, m_cfg.y, m_cfg.w, m_cfg.h, default_flags);
		// SDl log e.what()
	}

	Window::Window(WindowConfig const cfg) : m_cfg(cfg) // override base config
	{
		parse_flags();

		int default_flags = SDL_WINDOW_SHOWN & SDL_WINDOW_RESIZABLE;
		m_window = SDL_CreateWindow("Window", m_cfg.x, m_cfg.y, m_cfg.w, m_cfg.h, default_flags);
		// SDl log e.what()
		//exit();
		
	}
}