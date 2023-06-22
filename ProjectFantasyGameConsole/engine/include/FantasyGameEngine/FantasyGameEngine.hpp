#ifndef FANTASYGAMEENGINE_HPP
#define FANTASYGAMEENGINE_HPP

#ifdef _WIN32
#  define FGE_API __declspec(dllexport)
#else
#  define FGE_API
#endif

namespace FantasyGameEngine {

	FGE_API int test_sdl();
	FGE_API void test_lua();
	FGE_API int add(int a, int b);

}

#endif