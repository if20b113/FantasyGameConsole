#include "MemoryGrid.h"


void MemoryGrid::InitGrid(SDL_Renderer* ren, int rows, int columns ,int screenwidth, int screenheight) {

	CardsLeft = rows * columns;

	MemoryTotalheight = screenheight;

	MemoryTotalwidth = screenwidth;

	GridRows = rows;

	GridColumns = columns;

	CalculateGridCardsize();

	CenterGrid();

	int gridstartyup = gridStarty;

	int gridstartxup = gridStartx;

	int test = 1;

	for (int i = 0; i < GridRows; i++) {

		for (int y = 0; y < GridColumns; y++) {

			MemoryGrid[i][y].InitCard(ren, test, gridstartxup, gridstartyup,CardSize);

			gridstartxup += CardSize + 5;
			test++;

			if (test > 3) {

				test = 1;
			}
		}
		gridstartxup = gridStartx;
		gridstartyup += CardSize + 5;
	}
}

void MemoryGrid::CalculateGridCardsize() {

	int xcenter = MemoryTotalwidth / 2;
	
	int ycenter = MemoryTotalheight / 2;

	int AmmountofCardsPerRow = 0;

	int AmmoutofCardsPerColumn = 0;

	bool cardsfitGrid = false;

	while (!cardsfitGrid) {


		AmmoutofCardsPerColumn = (MemoryTotalwidth-200) / (CardSize + 5);

		AmmountofCardsPerRow = (MemoryTotalheight-200) / (CardSize + 5);

		if (AmmoutofCardsPerColumn >= GridColumns && AmmountofCardsPerRow >= GridRows) {

			cardsfitGrid = true;
			
		}
		else {

			CardSize -= 5;
		}
	}
}

void MemoryGrid::CenterGrid() {

	int TotalGridwidth = (CardSize + 5) * GridColumns;

	int TotalGridheight = (CardSize + 5) * GridRows;

	gridStartx = (MemoryTotalwidth-TotalGridwidth)/2;
	gridStarty = (MemoryTotalheight-TotalGridheight)/2;

}

void MemoryGrid::drawCards(SDL_Renderer* ren) {

	for (int i = 0; i < GridRows; i++) {

		for (int y = 0; y < GridColumns; y++) {

			MemoryGrid[i][y].drawCard(ren);
			if (!MemoryGrid[i][y].isValid) {
				CardsLeft--;
			}
		}
	}
}