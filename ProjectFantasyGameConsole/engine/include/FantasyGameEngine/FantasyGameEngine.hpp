#ifndef FANTASYGAMEENGINE_HPP
#define FANTASYGAMEENGINE_HPP

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
	struct FGE_Inputs
	{
		u32 down;
		u32 pressed;
	};

	typedef void FGE_Update(const FGE_Renderer* renderer, const FGE_Inputs* inputs);

	FGE_API void render_rect(const FGE_Renderer* renderer, float x, float y, float w, float h, float r, float g, float b);
	FGE_API void run(FGE_Update update_func);


	FGE_API int test_sdl();
	FGE_API void test_lua();
	FGE_API int add(int a, int b);

}

#endif