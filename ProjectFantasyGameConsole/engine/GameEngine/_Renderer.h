#pragma once

#include <string>

#include "SDL.h"
#include "_Window.h"
#include "_ImageObject.h"
#include "Renderer.h"

typedef std::unique_ptr<SDL_Renderer> RendererUPtr;
typedef std::shared_ptr<SDL_Texture> TextureSPtr;
namespace FGE 
{
	class EngineRenderer // Renderer owns Window and SDL renderer
		// It takes objects as input and renders them
		// It sets object's textures if they can have any.
		// It is able to change Window properties
	{
	private:
		SDL_Renderer* m_Renderer; // Only managed by this class
		Window* m_Window;
	public:
		EngineRenderer();
		EngineRenderer(WindowConfig cfg);
		~EngineRenderer();
		
		void RendererClear();
		void RendererDestroy();
		void RendererPresent();
		bool RenderObject(ImageObject* ImageObj);
		void RendererSetLogicalSize(int width, int height);
		void SetRenderDrawColor(int r, int g, int b, int a); // Not sure what this will do in any context
		bool LoadTexture(ImageObject* ImageObj, std::string texturepath); // Load texture into imageobj

	private:
		void DestroyRenderer();
	protected:
	};
}