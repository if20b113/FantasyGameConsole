#ifndef FANTASYGAMEENGINE_HPP
#define FANTASYGAMEENGINE_HPP

#include <unordered_map>
#include "SDL.h"
#include "SDL_ttf.h"
#include "glm/vec2.hpp"

typedef unsigned int u32;

namespace FantasyGameEngine {

	const u32 FGEKC_w = 0b0001;
	const u32 FGEKC_a = 0b0010;
	const u32 FGEKC_s = 0b0100;
	const u32 FGEKC_d = 0b1000;

	struct FGE_Renderer
	{
		SDL_Renderer* sdl_renderer;
	};

	typedef u32 FGE_ImageHandle;

	struct FGE_Image
	{
		SDL_Texture* sdl_texture;
		int w, h;
	};

	struct EngineState
	{
		FGE_ImageHandle next_image_handle = 1;
		std::unordered_map<FGE_ImageHandle, FGE_Image> images;
		TTF_Font* font;
	};

	struct FGE_Inputs
	{
		u32 down;
		u32 pressed;
	};

	typedef void FGE_InitFunc(
		const FGE_Renderer* renderer);

	typedef void FGE_UpdateFunc(
		const FGE_Inputs& inputs);

	typedef void FGE_RenderFunc(
		const FGE_Renderer* renderer,
		double delta);

	FGE_ImageHandle load_image(const FGE_Renderer* renderer, const char* path);
	void render_rect (const FGE_Renderer* renderer, const glm::vec2& pos, const glm::vec2& size, float r, float g, float b);
	void render_image(const FGE_Renderer* renderer, const glm::vec2& pos, const FGE_ImageHandle& image);
	void render_image(const FGE_Renderer* renderer, const glm::vec2& pos, const glm::vec2& size, const FGE_ImageHandle& image);
	void render_text (const FGE_Renderer* renderer, const glm::vec2& pos, const char* text);
	void run(
		FGE_InitFunc init_func,
		FGE_UpdateFunc update_func, 
		FGE_RenderFunc render_func, 
		double tick_length_ms);

	void print_sdl_error(const char* note);

	int test_sdl();
	void test_lua();

	extern EngineState fge_state;
}

#endif