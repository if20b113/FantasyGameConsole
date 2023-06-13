#pragma once
#include "core.h"
namespace FGE 
{
	enum ObjectType
	{
		NONE = 0,
		FONT = 1,
		AUDIO = 2,

		TEXT = 100, // 100. 
		IMAGE = 101,
	};
	enum class EventType
	{
		NONE = 0,
		OnClick = 1,
		OnCollision = 2
	};
	struct Event;
	struct GameObject; // Vec2D introduces SDL rects

	
}
