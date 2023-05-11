#include "Renderer.h"

EngineRenderer::EngineRenderer() {
	
}

void EngineRenderer::CreateRenderer(SDL_Window* window) {

	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void EngineRenderer::RendererClear() {

	SDL_RenderClear(m_Renderer);
}

void EngineRenderer::RendererObject(SDL_Texture* texture, SDL_Rect srect,SDL_Rect drect) {

	SDL_RenderCopy(m_Renderer, texture, &srect, &drect);
}

void EngineRenderer::RendererPresent() {

	SDL_RenderPresent(m_Renderer);
}

void EngineRenderer::RendererDestroy() {

	SDL_DestroyRenderer(m_Renderer);
}

void EngineRenderer::RendererText() {

	//SDL_RenderCopy(renderer, texture, NULL, &text_rectangle);
}

SDL_Texture* EngineRenderer::LoadTexture(std::string texturepath) {

	SDL_Texture* texture = IMG_LoadTexture(m_Renderer, texturepath.c_str());

	return texture;
}

void EngineRenderer::RendererSetLogicalSize(int width, int height) {

	SDL_RenderSetLogicalSize(m_Renderer, width, height);
}

void EngineRenderer::SetRenderDrawColor (int r, int g ,int b, int a){

	SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
}

void EngineRenderer::DestroyRenderer() {

	SDL_DestroyRenderer(m_Renderer);
}



