#include <filesystem>

#include "_Renderer.h"
#include <SDL.h>


namespace FGE 
{
	EngineRenderer::EngineRenderer()
	{
		Window win;
		m_Window = &win;;
		m_Renderer = SDL_CreateRenderer(m_Window->GetWindow(), -1, SDL_RENDERER_ACCELERATED);
	}
	EngineRenderer::EngineRenderer(WindowConfig cfg)
	{
		Window win(cfg);
		m_Window = &win;;
		m_Renderer = SDL_CreateRenderer(m_Window->GetWindow(), -1, SDL_RENDERER_ACCELERATED);
	}
	EngineRenderer::~EngineRenderer()
	{
		DestroyRenderer();
	}
	void EngineRenderer::RendererClear() {

		if (m_Renderer)
		{
			SDL_RenderClear(m_Renderer);
		}
	}

	bool EngineRenderer::RenderObject(ImageObject* ImageObj) 
	{
		if (m_Renderer && ImageObj->IsLoaded())
		{
			if (!SDL_RenderCopy(m_Renderer, ImageObj->GetTexture(), &ImageObj->GetSrect(), &ImageObj->GetDrect()))
			{
				return true;
			}
			// SDL Error code. RenderObj failed.
			return false;
		}

		return false;
	}

	void EngineRenderer::RendererPresent() 
	{
		if (m_Renderer)
		{
			SDL_RenderPresent(m_Renderer);
		}
	}
	void EngineRenderer::RendererDestroy() 
	{
		if (m_Renderer)
		{
			SDL_DestroyRenderer(m_Renderer);
		}
	}

	bool EngineRenderer::LoadTexture(ImageObject* ImageObj, std::string texturepath)
	{
		if (!std::filesystem::exists(texturepath))
		{
			std::cout << " Load texture failed. file does not exist\n";
			return false;
		}

		if (!m_Renderer)
		{		
			// Log: Load texture failed. Renderer not found.
			std::cout << " Load texture failed. Renderer not found.\n";
			return false;
		}	

		if (!ImageObj)
		{
			// Log: Load texture failed. ImageObj is nullptr
			std::cout << "load texture failed. ImageObj is nullptr\n";
			return false;
		}
		char errMsgBuf[1024] = {};
		SDL_GetErrorMsg(errMsgBuf, 1024);
		printf("sdl error: %s\n", errMsgBuf);

		auto newTexture = IMG_LoadTexture(m_Renderer, texturepath.c_str());
		printf("newTexture:%d after load %s\n", (long long)newTexture, texturepath.c_str());

		memset(errMsgBuf, 0, 1024);
		SDL_GetErrorMsg(errMsgBuf, 1024);
		printf("sdl error: %s\n", errMsgBuf);

		if (!newTexture)
		{
			std::cout << "load texture failed. newTexture is nullptr\n";
			return false;
		}

		ImageObj->ChangeTexture(newTexture);

		if (!ImageObj->IsLoaded())
		{
			std::cout << "load texture failed. imageobj is not loaded\n";
			return false;
		}

		return true;
	}

	void EngineRenderer::RendererSetLogicalSize(int width, int height) 
	{
		if (m_Renderer)
		{
			SDL_RenderSetLogicalSize(m_Renderer, width, height);
		}
	}

	void EngineRenderer::SetRenderDrawColor(int r, int g, int b, int a) 
	{
		if (m_Renderer)
		{
			SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
		}
		
	}

	void EngineRenderer::DestroyRenderer() 
	{
		if (m_Renderer)
		{
			SDL_DestroyRenderer(m_Renderer);
		}
		
	}


}

