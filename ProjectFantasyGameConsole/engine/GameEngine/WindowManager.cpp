#include "WindowManager.h"
#include <iostream>
namespace FGE
{
	Window::Window() // cfg is by default intialized with values
	{
		try
		{
			m_window = SDL_CreateWindow("Window", m_cfg.x, m_cfg.y, m_cfg.w, m_cfg.h, m_cfg.flags);
		}
		catch (std::exception e)
		{
			// SDl log e.what()
		}
	}
	Window::Window(WindowConfig const cfg) : m_cfg(cfg) // override base config
	{
		try
		{
			m_window = SDL_CreateWindow("Window", m_cfg.x, m_cfg.y, m_cfg.w, m_cfg.h, m_cfg.flags);
		}
		catch (std::exception e)
		{
			// SDl log e.what()
			//exit();
		}
	}
}