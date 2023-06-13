#include "_Vec.h"
namespace FGE
{
	void Vec2D::Clear()
	{
		srect.x = 0;
		srect.y = 0;
		drect.x = 0;
		drect.y = 0;
	}
	SDL_Rect Vec2D::GetSrect()
	{
		return srect;
	}

	SDL_Rect Vec2D::GetDrect()
	{
		return drect;
	}

	void Vec2D::AddVectorSrect(int const Addx, int const Addy) // Add to visual size
	{
		srect.x += Addx;
		srect.y += Addy;
	};
	void Vec2D::AddVectorDrect(int const Addx, int const Addy) // Add to Hitbox size
	{
		drect.x += Addx;
		drect.y += Addy;
	};
	void Vec2D::SetVectorBoth(int const x, int const y)
	{
		srect.x = x;
		srect.y = y;
		drect.x = x;
		drect.y = y;
	};
}
