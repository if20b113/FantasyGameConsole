#ifndef FANTASYGAMEENGINE_HPP
#define FANTASYGAMEENGINE_HPP

#include "glm/vec2.hpp"

#ifdef _WIN32
#  define FGE_API __declspec(dllexport)
#else
#  define FGE_API
#endif

typedef unsigned int u32;

namespace FantasyGameEngine {

	const u32 FGEKC_w = 0b0001;
	const u32 FGEKC_a = 0b0010;
	const u32 FGEKC_s = 0b0100;
	const u32 FGEKC_d = 0b1000;

	struct FGE_Renderer;
	typedef u32 FGE_ImageHandle;
	struct FGE_Inputs
	{
		u32 down;
		u32 pressed;
	};

	typedef void FGE_Init(
		const FGE_Renderer* renderer);

	typedef void FGE_Update(
		const FGE_Inputs* inputs);

	typedef void FGE_Render(
		const FGE_Renderer* renderer,
		double delta);

	FGE_API FGE_ImageHandle load_image(const FGE_Renderer* renderer, const char* path);
	FGE_API void render_rect (const FGE_Renderer* renderer, const glm::vec2& pos, const glm::vec2& size, float r, float g, float b);
	FGE_API void render_image(const FGE_Renderer* renderer, const glm::vec2& pos, const FGE_ImageHandle& image);
	FGE_API void render_image(const FGE_Renderer* renderer, const glm::vec2& pos, const glm::vec2& size, const FGE_ImageHandle& image);
	FGE_API void render_text (const FGE_Renderer* renderer, const glm::vec2& pos, const char* text);
	FGE_API void run(
		FGE_Init init_func,
		FGE_Update update_func, 
		FGE_Render render_func, 
		double tick_length_ms);

	FGE_API int test_sdl();
	FGE_API void test_lua();
	FGE_API int add(int a, int b);

}

#endif