#include "TetrisRenderer.h"

FantasyGameEngine::TetrisRenderer::TetrisRenderer()
{
}

void FantasyGameEngine::TetrisRenderer::init(const FGE_Renderer* renderer)
{
	m_renderer = renderer;
	this->m_blocks = load_image(renderer, "assets/blocks.png");

}

void FantasyGameEngine::TetrisRenderer::RenderBlock(int gridvalue, int posx, int posy, int sizex, int sizey)
{
	

	switch (gridvalue) {
	case 1:
		FantasyGameEngine::render_image_sprite(m_renderer,
		{posx,posy},
		{ sizex,sizey }, { 0,36 }, { 36,36 },
		m_blocks);
		break;
	case 2:
		FantasyGameEngine::render_image_sprite(m_renderer,
		{posx,posy},
		{ sizex,sizey }, { 36,36 }, { 36,36 },
		m_blocks);
		break;
	case 3:
		FantasyGameEngine::render_image_sprite(m_renderer,
			{ posx,posy },
			{ sizex,sizey }, { 36*2,36 }, { 36,36 },
			m_blocks);
		break;
	case 4:
		FantasyGameEngine::render_image_sprite(m_renderer,
			{ posx,posy },
			{ sizex,sizey }, { 36*3,36 }, { 36,36 },
			m_blocks);
		break;
	case 5:
		FantasyGameEngine::render_image_sprite(m_renderer,
			{ posx,posy },
			{ sizex,sizey }, { 36*4,36 }, { 36,36 },
			m_blocks);
		break;
	case 6:
		FantasyGameEngine::render_image_sprite(m_renderer,
			{ posx,posy },
			{ sizex,sizey }, { 36 * 5,36 }, { 36,36 },
			m_blocks);
		break;
	case 7:
		FantasyGameEngine::render_image_sprite(m_renderer,
			{ posx,posy },
			{ sizex,sizey }, { 36 * 6,36 }, { 36,36 },
			m_blocks);
		break;
	case 8:
		FantasyGameEngine::render_image_sprite(m_renderer,
			{ posx,posy },
			{ sizex,sizey }, { 36 * 7,36 }, { 36,36 },
			m_blocks);
		break;
	default:
		FantasyGameEngine::render_rect(m_renderer,
			{ posx,posy },
			{ sizex - 1,  sizey - 1 },
			0, 0, 0);
	}

	
}

void FantasyGameEngine::TetrisRenderer::calculategridoffset(int gridsizex, int gridsizey, int cell_size_x, int cell_size_y, int screenwidth,int screenheight)
{
	int x = screenwidth / 2;

	int y = screenheight / 2;

	int gridlength = cell_size_x * gridsizex;

	int gridheight = cell_size_y * gridsizey;

	 int gridx = x - gridlength/2;

	 int gridy = y - gridheight/2;

	gridoffset = { gridx,gridy };
}
