#pragma once

#include <string>

#include "SDL.h"

#include "ImageObject.h"

namespace FGE 
{
	class EngineRenderer {

	public:
		EngineRenderer();
		void CreateRenderer(SDL_Window* window);
		void RendererClear();
		void RendererDestroy();
		void RendererPresent();
		void RendererObject(SDL_Texture* texture, SDL_Rect srect, SDL_Rect drect);
		void RendererText();
		void RendererSetLogicalSize(int width, int height);
		void SetRenderDrawColor(int r, int g, int b, int a);
		void DestroyRenderer();
		SDL_Texture* LoadTexture(std::string texturepath);


	private:
		SDL_Renderer* m_Renderer;
	protected:


	};
}
