#pragma once
#include "FantasyGameEngine.hpp"
#include <string>


namespace FantasyGameEngine
{
	class UIRenderer
	{
	public:

		bool isinMainMenu = true;
		bool isinGame = false;
		bool isinHighscore = false;
		bool isinControls = false;
		bool running = true;
		bool ispaused = false;
		bool isenteringName = false;
		bool Gamestarted = false;
		bool selectGameMode = false;
		bool startnewgame = false;
		bool nameconfirmed = false;
		bool loadgame = false;
		bool savegame = false;
		int menubutton = 1;
		int pausebutton = 1;
		int gamemodebutton = 1;
		char playername[5] = "....";
		int abccounter = 0;
		int index = 0;

		UIRenderer();
		void init(const FGE_Renderer* renderer, int width, int height);
		void draw_ui();
		void get_scores(std::vector<std::tuple<std::string, int>> highscores);
		void HandleInput();
		void calculate_ui_positions();
		void checkbuttonint();
		void draw_pause_menu();
		void draw_score_ui();
		void handlegameover();
		void addscore(int score);

	private:
		const FGE_Renderer* m_renderer;
		int m_height = 0;
		int m_width = 0;
		FGE_ImageHandle m_logo;
		FGE_ImageHandle m_title;
		FGE_ImageHandle m_buttons;
		glm::vec2 start_button_pos;
		glm::vec2 score_button_pos;
		glm::vec2 exit_button_pos;
		glm::vec2 title_pos;
		glm::vec2 controls_button_pos;
		std::vector<std::tuple<std::string, int>> scores;
	};
}

