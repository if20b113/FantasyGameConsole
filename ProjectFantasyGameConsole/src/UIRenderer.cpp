#include "UIRenderer.h"

FantasyGameEngine::UIRenderer::UIRenderer()
{

}

void FantasyGameEngine::UIRenderer::init(const FGE_Renderer* renderer, int width, int height)
{
	m_renderer = renderer;
	m_logo = load_image(m_renderer, "assets/FH_Technikum_Wien_logo.png");
	m_title = load_image(m_renderer, "assets/Tetris_logo.png");
	m_buttons = load_image(m_renderer, "assets/Buttons_UI.png");

	this->m_height = height;
	this->m_width = width;

	std::tuple<std::string, int> testtuple;

	testtuple = std::make_tuple("Test1", 10);

	scores.push_back(testtuple);

	testtuple = std::make_tuple("Test2", 8);

	scores.push_back(testtuple);

	testtuple = std::make_tuple("Test3", 7);

	scores.push_back(testtuple);

	calculate_ui_positions();
}

void FantasyGameEngine::UIRenderer::draw_ui()
{
	if (!isinGame)
	{
		if (isinMainMenu)
		{
			FantasyGameEngine::render_image(m_renderer, { 5,5 }, { 150,100 }, m_logo);

			FantasyGameEngine::render_image(m_renderer, title_pos, { 400,200 }, m_title);

			switch (menubutton)
			{
			case 1:
				FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 0,0 }, { 400,100 }, m_buttons); //start
				FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 400,200 }, { 400,100 }, m_buttons); //score
				FantasyGameEngine::render_image_sprite_ui(m_renderer, controls_button_pos, { 300,75 }, { 400,300 }, { 400,100 }, m_buttons); //controls
				FantasyGameEngine::render_image_sprite_ui(m_renderer, exit_button_pos, { 300,75 }, { 400,100 }, { 400,100 }, m_buttons); //exit
				break;
			case 2:
				FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 400,0 }, { 400,100 }, m_buttons); //start
				FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 0,200 }, { 400,100 }, m_buttons); //score
				FantasyGameEngine::render_image_sprite_ui(m_renderer, controls_button_pos, { 300,75 }, { 400,300 }, { 400,100 }, m_buttons); //controls
				FantasyGameEngine::render_image_sprite_ui(m_renderer, exit_button_pos, { 300,75 }, { 400,100 }, { 400,100 }, m_buttons); //exit
				break;
			case 3:
				FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 400,0 }, { 400,100 }, m_buttons); //start
				FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 400,200 }, { 400,100 }, m_buttons); //score
				FantasyGameEngine::render_image_sprite_ui(m_renderer, controls_button_pos, { 300,75 }, { 0,300 }, { 400,100 }, m_buttons); //controls
				FantasyGameEngine::render_image_sprite_ui(m_renderer, exit_button_pos, { 300,75 }, { 400,100 }, { 400,100 }, m_buttons); //exit
				break;
			case 4:
				FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 400,0 }, { 400,100 }, m_buttons); //start
				FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 400,200 }, { 400,100 }, m_buttons); //score
				FantasyGameEngine::render_image_sprite_ui(m_renderer, controls_button_pos, { 300,75 }, { 400,300 }, { 400,100 }, m_buttons); //controls
				FantasyGameEngine::render_image_sprite_ui(m_renderer, exit_button_pos, { 300,75 }, { 0,100 }, { 400,100 }, m_buttons); //exit
				break;
			default:
				FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 400,0 }, { 400,100 }, m_buttons); //start
				FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 400,200 }, { 400,100 }, m_buttons); //score
				FantasyGameEngine::render_image_sprite_ui(m_renderer, controls_button_pos, { 300,75 }, { 400,300 }, { 400,100 }, m_buttons); //controls
				FantasyGameEngine::render_image_sprite_ui(m_renderer, exit_button_pos, { 300,75 }, { 400,100 }, { 400,100 }, m_buttons); //exit
			}

		}
		if (isinHighscore)
		{
			if (!scores.empty()) {
				render_text(m_renderer, { m_width / 2 - 20, 5 }, "High Score");
				for (int i = 0; i < (int)scores.size(); i++)
				{
					std::string test = std::to_string(i + 1);
					test += ".";

					std::tuple<std::string, int> score = scores.at(i);
					std::string playername = std::get<0>(score);
					std::string playerscore = std::to_string(std::get<1>(score));


					render_text(m_renderer, { (m_width / 2) - 50, 100 + 50 * i }, test.c_str());
					render_text(m_renderer, { m_width / 2, 100 + 50 * i }, playername.c_str());
					render_text(m_renderer, { (m_width / 2) + 100, 100 + 50 * i }, playerscore.c_str());
				}
			}
			else
			{
				render_text(m_renderer, { (m_width / 2) - 100, (m_height / 2) - 50 }, "No Games Played");
			}

		}
		if (isinControls)
		{
			render_text(m_renderer, { m_width / 2, 5 }, "Controls");
		}
		//if()
	}

}

void FantasyGameEngine::UIRenderer::get_scores(std::vector<std::tuple<std::string, int>> highscores)
{
	scores = highscores;
}


void FantasyGameEngine::UIRenderer::HandleInput()
{
	if (!isinGame) 
	{
		if (isinMainMenu)
		{
			switch (menubutton) 
			{
			case 1: 
				isinGame = true; 
				isinMainMenu = false;
				break;
			case 2: 	
			    isinMainMenu = false;
				isinHighscore = true;
				break;
			case 3:
				isinMainMenu = false;
				isinControls = true;
				break;
			case 4:
				isinMainMenu = false;
				running = false;
				break;
			default:
				isinMainMenu = true;
				menubutton = 1;
			}
		}
		else if (isinHighscore)
		{
			isinMainMenu = true;
			isinHighscore = false;
		}
		else if (isinControls) {
			isinMainMenu = true;
			isinControls = false;
		}
			
	}
	if (ispaused)
	{
		if (pausebutton == 2)
		{
			ispaused = false;
			isinGame = false;
			isinMainMenu = true;
		}
	}
}

void FantasyGameEngine::UIRenderer::calculate_ui_positions()
{
	int x = m_width / 2;

	int y = m_height / 2;

	start_button_pos = { x-150 ,y - 100 };

	score_button_pos = {x - 150,y};

	controls_button_pos = { x - 150,y+100};

	exit_button_pos = { x - 150,y+200 };

	title_pos = { x - 200  , y - 350 };

}

void FantasyGameEngine::UIRenderer::checkbuttonint() 
{
	if (menubutton > 4) {
		menubutton = 4;
	}
	if (menubutton < 1) {
		menubutton = 1;
	}
	if (index < 0) {
		index = 0;
	}
	if (index > 4) {
		index = 4;
	}
	if (abccounter < 0) {
		abccounter = 25;
	}
	if (abccounter > 25) {
		abccounter = 0;
	}
	if (pausebutton < 1) 
	{
		pausebutton = 1;
	}
	if (pausebutton > 2)
	{
		pausebutton = 2;
	}
}

void FantasyGameEngine::UIRenderer::draw_pause_menu()
{
	if (ispaused)
	{
		render_rect(m_renderer, { 0,0 }, { 1280,720 }, 0, 0, 0, 0.5);
		if(pausebutton == 1)
		{
			FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 0,500 }, { 400,100 }, m_buttons); //save
			FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 400,400 }, { 400,100 }, m_buttons); //Main Menu
		}
		if (pausebutton == 2)
		{
			FantasyGameEngine::render_image_sprite_ui(m_renderer, start_button_pos, { 300,75 }, { 400,500 }, { 400,100 }, m_buttons); //Save
			FantasyGameEngine::render_image_sprite_ui(m_renderer, score_button_pos, { 300,75 }, { 0,400 }, { 400,100 }, m_buttons); //Main Menu
		}
	}
}

void FantasyGameEngine::UIRenderer::draw_score_ui()
{
		playername[index] = 65 + abccounter;

		render_text(m_renderer, { m_width / 2-250,m_height / 2 }, "Enter your name:");

		render_text(m_renderer, { m_width / 2,m_height / 2 }, playername);
}



