#include "WindowManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <list>

SDL_Window* WindowManager::createWindow(const char* const title)
{
	// Create the requested window and set it into the class list.
	// Function takes only takes title arg

	SDL_Window* window = SDL_CreateWindow(title, m_cfg.x, m_cfg.y, m_cfg.w, m_cfg.h, m_cfg.flags);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	WindowStorage store;
	store.winTitle = title;
	store.winPtr = window;
	store.winRend = renderer;

	m_windows.push_back(store); // Add the window to the list of windows in the manager
	return window;
}

WindowStorage* WindowManager::getWindow(void* term, SearchTerm perTerm)
{
	// Usage: WindowStorage window = manager.getWindow("MyWindow", PerTitle");
	char* title = NULL;
	SDL_Window* window = NULL;
	switch (perTerm)
	{
	case PER_TITLE:
		title = static_cast<char*>(term); // Interpret as string

			for (auto iter = m_windows.begin(); iter != m_windows.end(); ++iter)
			{
				if (!strcmp((*iter).winTitle, title))
				{
					return &(*iter);
				}
			}
		
		break;
	case PER_PTR:
		// Why does this exist? Maybe you need the title OR the renderer?
		window = static_cast<SDL_Window*>(term); // Interpret as pointer

			for (auto iter = m_windows.begin(); iter != m_windows.end(); ++iter)
			{
				if ((*iter).winPtr == window)
				{
					return &(*iter);
				}
			}
		
		break;
	}
	std::cout << "Could not find the window.\n";
	return NULL;
}

WindowManager::WindowManager() 
{
	SDL_Init(SDL_INIT_EVERYTHING);
}
WindowManager::~WindowManager()
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); ++iter)
	{
		TTF_CloseFont((*iter).s_Font);
		SDL_DestroyRenderer((*iter).winRend);
		SDL_DestroyWindow((*iter).winPtr);
	}

	TTF_Quit();
	SDL_Quit();
}

void WindowManager::RenderWindow(SDL_Window* const window)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); ++iter)
	{
		if ((*iter).winPtr == window)
		{
			SDL_RenderPresent((*iter).winRend);
			return;
		}
	}
	
	std::cout << "Error cannot find the window ptr to render. Did you pass in a pointer that lives inside the class?\n";
}
void WindowManager::RenderWindow(SDL_Renderer* const renderer)
{

	for (auto iter = m_windows.begin(); iter != m_windows.end(); ++iter)
	{
		if ((*iter).winRend == renderer)
		{
			SDL_RenderPresent((*iter).winRend);
			return;
		}
	}
	std::cout << "Error cannot find the render ptr to render. Did you pass in a pointer that lives inside the class?\n";
}

void WindowManager::displayText(const int x, const int y, const std::string& text, const WindowStorage& storage)
{
	// Does not support custom color or font size yet
	TTF_Init();
	TTF_Font* font = loadFont(m_fontPath, m_defaultFontSize);
	if (font == NULL)
	{
		return;
	}
		
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), m_defaultColor);
	if (!text_surface)
	{
		std::cout << std::endl << "Failed to create surface\n";
		return;
	}

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(storage.winRend, text_surface);
	if (!text_texture)
	{
		std::cout << std::endl << "Failed to create texture\n";
		return;
	}

	SDL_FreeSurface(text_surface);
	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h); // Get text dimension
	SDL_Rect textRect = { m_cfg.w / 2 - w / 2, m_cfg.h / 2 - h / 2, w, h }; // Render text
	SDL_RenderClear(storage.winRend); // Clear the window
	SDL_RenderCopy(storage.winRend, text_texture, NULL, &textRect);
	SDL_DestroyTexture(text_texture);

	// Update screen
	SDL_RenderPresent(storage.winRend);


}
// Functions copied from Scoreboard.
TTF_Font* WindowManager::loadFont(const std::string& font_path, int font_size)
{
	std::string path = font_path;
	if (path.empty())
	{
		path = m_fontPath;
	}

	TTF_Font* font = TTF_OpenFont(m_fontPath.c_str(), font_size);
	if (font == NULL) 
	{
		std::cout << std::endl << "Could not load font\n";
		return NULL;
	}


	//SDL_FreeSurface(text_surface);
	//TTF_CloseFont(font);

	return font;
}