#pragma once

#include "core.h"

namespace FGE {

    enum WindowFlags : u32
    {
        FGE_WF_None = 0,
        FGE_WF_Centered = 1,
    };

    struct WindowConfig
	{
		int x = 0;
		int y = 0;
		int w = 600;
		int h = 400;
		WindowFlags flags = FGE_WF_Centered;
	};

    struct Window;

}