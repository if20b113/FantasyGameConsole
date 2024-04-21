#pragma once
#include "FantasyGameEngine.hpp"

namespace FantasyGameEngine
{
	class TetrisRenderer
	{
	public:
		TetrisRenderer();
		void init(const FGE_Renderer* renderer);
		//void RenderBlock(int gridvalue, const glm::vec2& size, const glm::vec2& pos);
		void RenderBlock(int gridvalue, int posx, int posy, int sizex, int sizey);
		void calculategridoffset(int gridsizex, int gridsizey, int cell_size_x, int cellsize_y, int screenwidth, int screenheight);
		glm::vec2 gridoffset;

	private:
		FGE_ImageHandle m_blocks;
		const FGE_Renderer* m_renderer;

	};

}


