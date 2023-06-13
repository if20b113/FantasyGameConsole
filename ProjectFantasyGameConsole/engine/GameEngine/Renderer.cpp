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
		
		if (m_Renderer)
		{
			if (ImageObj)
			{
				ImageObj->ChangeTexture(IMG_LoadTexture(m_Renderer, texturepath.c_str()));
				if(ImageObj->IsLoaded())
					return true;
			}
			// Log: Load texture failed. ImageObj is nullptr
			return false;
			
		}		
		// Log: Load texture failed. Renderer not found.
		return false;
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

