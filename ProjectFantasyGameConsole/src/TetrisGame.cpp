#include "TetrisGame.h"
#include "constants.h"
#include "Tetromino.h"
#include "MutEx.h"
#include <iostream>
#include <map>
#include <random>

TetrisGame::TetrisGame()
{
	level = 1; 
	score = 0;
	paused = false;
	for (int i = 0; i < GAME::gameSize_X; i++)
		for (int j = 0; j < GAME::gameSize_Y; j++)
			gameField[i][j] = PieceColor::COLOR_BACKGROUND;
	InitNewPiece();
}
TetrisGame::~TetrisGame()
{
	if (currentPiece)
		delete currentPiece;
	if (nextPiece)
		delete nextPiece;
}
bool TetrisGame::CheckValidMove(CoordinateSet moveVec) const
{
	if (!currentPiece)
		return false;

	if (moveVec.size() != GAME::MAX_BLOCK_COUNT)
		return false; // Move vector is invalid

	size_t CurrAt = 0;
	for (auto it: moveVec)
	{
		// 1. Does it move at all?
		if (it.sPos_x == 0 && it.sPos_y == 0)
		{
			CurrAt++;
			continue; // This specific position won't move
		}

		size_t const CurrX = currentPiece->GetXAt(CurrAt);
		size_t const CurrY = currentPiece->GetYAt(CurrAt);
		
		// 2. Boundary check
		if ((CurrX + it.sPos_x) > GAME::gameSize_X		||
			(CurrX + it.sPos_x) < GAME::LowBoundary_X	||
			(CurrY + it.sPos_y) > GAME::gameSize_Y		||
			(CurrY + it.sPos_y) < GAME::LowBoundary_Y)
			return false;// This piece would land out of bounds. Move not possible
		
		// 3. Check for blocks in the way
		if (gameField[CurrX + it.sPos_x][CurrY + it.sPos_y] != PieceColor::COLOR_BACKGROUND)
		{
			// Is the block that is in my way mine?
			if(!currentPiece->HavePosition({short( CurrX + it.sPos_x), short(CurrY + it.sPos_y)}))
				return false; // No this block doesn't belong to me and I cannot move there.
		}
			
		CurrAt++;
	}
	return true;
}
bool TetrisGame::CheckValidMove(MoveDirection dir) const
{
	if (!currentPiece)
		return false;

	auto fillDuplicate = [](CoordinateSet& moveVec, PiecePosition const& movePos)
		{
			for (int i = 0; i < GAME::MAX_BLOCK_COUNT; i++)
				moveVec.push_back(movePos);
		};
	CoordinateSet moveVec;
	switch (dir)
	{
	case MoveDirection::LEFT:
	{
		fillDuplicate(moveVec, { -1, 0 });
	}break;
	case MoveDirection::RIGHT:
	{
		fillDuplicate(moveVec, { 1, 0 });
	}break;
	case MoveDirection::DOWN:
	{
		// Not implemented?
		fillDuplicate(moveVec, { 0, 1 });
	}break;
	default:
	{ // None?
		fillDuplicate(moveVec, { 0, 0 });
	}break;
	}

	return CheckValidMove(moveVec);
}
int TetrisGame::CalculatePoints(size_t const RowCount) const
{
	return RowCount * (40 * (level + 1));
}
void TetrisGame::DeleteAndMoveDownRows(std::vector<int> const& rowNumbers)
{
	MutEX mute;
	// THIS function should REALLY be unit tested btw.
	// The numbers are sorted small to large
	for (auto it : rowNumbers)
	{
		// Set background of affected row to background color
		for (int i = 0; i < GAME::gameSize_X; i++)
			gameField[i][it] = PieceColor::COLOR_BACKGROUND;
	}
	// Save info from rows with blocks.
	std::map<int, std::vector<PieceColor>> Rows;

	for (int j = (GAME::gameSize_Y - 1); j >= GAME::LowBoundary_Y; j--)
	{
		bool RowEmpty = true;
		std::vector<PieceColor> Blocks;
		for (int i = GAME::LowBoundary_X; i < GAME::gameSize_X; i++)
		{
			Blocks.push_back(gameField[i][j]);
			if (gameField[i][j] != PieceColor::COLOR_BACKGROUND)
			{
				RowEmpty = false;
				break;
			}
		}
		if (RowEmpty)
			Rows.emplace(j, Blocks);
	}
	// Empty out field
	for (int j = (GAME::gameSize_Y - 1); j >= GAME::LowBoundary_Y; j--)
		for (int i = GAME::LowBoundary_X; i < GAME::gameSize_X; i++)
			gameField[i][j] = PieceColor::COLOR_BACKGROUND;
		
	// Redraw the blocks
	for (auto it : Rows)
		for (auto it2 : it.second)
			for (int i = GAME::LowBoundary_X; i < GAME::gameSize_X; i++)
				gameField[i][it.first] = it2;
}
int TetrisGame::GenRandomNumber()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(1, 7);
	return distribution(gen);
}

bool TetrisGame::CheckHitBottom() const
{
	// checks whether the next Y for any block in the piece is taken.
	// If so, the piece will be stopped and the new piece will be initiated.
	// Make sure the piece doesnt take it's own blocks as stopper
	// Call at the end of the loop
	return CheckValidMove(MoveDirection::DOWN);
}
void TetrisGame::CheckForTetrisAndProcess()
{
	//int lines = 0;
	std::vector<int> rowNumbers; // Which rows to be deleted and converted to points
	for (int j = 0; j < GAME::gameSize_Y; j++) // Column top to bot
		for(int i = 0; i < GAME::gameSize_X; i++) // Row
		{
			if (gameField[i][j] == PieceColor::COLOR_BACKGROUND)
				break; // break out of this loop because it is out of option we have a tetris
			if (i == GAME::gameSize_X - 1) // last position is block 
				rowNumbers.push_back(j);
			
		}

	score += CalculatePoints(rowNumbers.size());
	DeleteAndMoveDownRows(rowNumbers);
}
bool TetrisGame::MovePiece(CoordinateSet moveVec)
{
	MutEX mute;
	if (!CheckValidMove(moveVec))
		return false;

	// Here we need to do 2 loops because of self overwriting
	// If a block of a piece moves into a spot where one of its own blocks was before, it may lead to missing behaviour
	// So it's better to separate those steps that they dont happen to overwrite themselves
	// Check valid move already checked whether the target spot 
	for (int i = 0; i < GAME::MAX_BLOCK_COUNT; i++)
	{
		//Make old field background
		gameField[currentPiece->GetXAt(i)][currentPiece->GetYAt(i)] = PieceColor::COLOR_BACKGROUND;
	}
	size_t CurrAt = 0;

	for (auto coord : moveVec)
	{
		if (coord.sPos_x == 0 && coord.sPos_y == 0)
		{
			CurrAt++;
			continue; // This specific position won't move
		}

		short const xNew = currentPiece->GetXAt(CurrAt) + coord.sPos_x;
		short const yNew = currentPiece->GetYAt(CurrAt) + coord.sPos_y;

		// Set new color
		gameField[xNew][yNew] = currentPiece->GetColor();

		// Set new position
		PiecePosition newPos{ xNew , yNew };
		currentPiece->SetCurrentPositionsAt(newPos, CurrAt);
		CurrAt++;
	}
	return true;
}
bool TetrisGame::MovePiece(MoveDirection dir)
{
	if (!currentPiece)
		return false;

	auto fillDuplicate = [](CoordinateSet& moveVec, PiecePosition const& movePos)
		{
			for (int i = 0; i < GAME::MAX_BLOCK_COUNT; i++)
				moveVec.push_back(movePos);
		};
	CoordinateSet moveVec;
	switch (dir)
	{
	case MoveDirection::LEFT:
	{
		fillDuplicate(moveVec, { -1, 0 });
	}break;
	case MoveDirection::RIGHT:
	{
		fillDuplicate(moveVec, { 1, 0 });
	}break;
	case MoveDirection::DOWN:
	{
		// Not implemented?
		fillDuplicate(moveVec, { 0, 1 });
	}break;
	default:
	{ // None?
		fillDuplicate(moveVec, { 0, 0 });
	}break;
	}

	return MovePiece(moveVec);
}
bool TetrisGame::RotateCurrentPiece()
{
	if (!currentPiece)
		return false;
	return MovePiece(currentPiece->GetNextRotation());
}
void TetrisGame::InitNewPiece()
{
	if (!currentPiece)
	{
		switch (GenRandomNumber())
		{
		case 1:
			currentPiece = new I_Piece();
			break;
		case 2:
			currentPiece = new J_Piece();
			break;
		case 3:
			currentPiece = new L_Piece();
			break;
		case 4:
			currentPiece = new O_Piece();
			break;
		case 5:
			currentPiece = new S_Piece();
			break;
		case 6:
			currentPiece = new T_Piece();
			break;		
		case 7:
			currentPiece = new Z_Piece();
			break;
		default:
			currentPiece = new I_Piece();
			break;
		}	
	}
	if (!nextPiece)
	{
		switch (GenRandomNumber())
		{
		case 1:
			nextPiece = new I_Piece();
			break;
		case 2:
			nextPiece = new J_Piece();
			break;
		case 3:
			nextPiece = new L_Piece();
			break;
		case 4:
			nextPiece = new O_Piece();
			break;
		case 5:
			nextPiece = new S_Piece();
			break;
		case 6:
			nextPiece = new T_Piece();
			break;
		case 7:
			nextPiece = new Z_Piece();
			break;
		default:
			nextPiece = new I_Piece();
			break;
		}
	}
}
void TetrisGame::GameLoop()
{
	MutEX mute;
	if (pauseBuffered)
	{
		pauseBuffered = false;
	}
	else
	{
		if (!paused)
		{
			// 1. Initiate piece if there isn't any
			// 2. Check bottom 
			// 3. If bottom check fine -> Move down
			// 3a Else set down make new piece
			InitNewPiece();
			if (!CheckHitBottom())
			{
				// Move down
				MovePiece(MoveDirection::DOWN);
			}
			else
			{
				// Piece cannot move down anymore -> set piece down and make a new one
				if (currentPiece) 
				{
					delete currentPiece;
				}
				currentPiece = nullptr;
				currentPiece = nextPiece;
				nextPiece = nullptr;
				InitNewPiece();
			}
		}
		else
		{

		}
	}
	
}
