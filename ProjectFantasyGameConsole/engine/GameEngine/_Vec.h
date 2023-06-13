#pragma once
#include "Vec.h"
#include <SDL.h>
namespace FGE 
{
	class Vec2D
	{
	private:

	protected:
		// Intentionally not using m_
		SDL_Rect srect;
		SDL_Rect drect;
	public:

		Vec2D()
		{
			Clear();
		};
		void Clear();
		void AddVectorSrect(int const Addx, int const Addy);
		void AddVectorDrect(int const Addx, int const Addy);
		void SetVectorBoth(int const x, int const y);

		SDL_Rect GetSrect();
		SDL_Rect GetDrect();
	};


}
