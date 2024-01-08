#pragma once
#include "Tetromino.h"
#include "constants.h"

enum class MoveDirection
{
	NONE = 0,
	LEFT,
	RIGHT,
	DOWN, // May not be implemented at first -> do it later
};

class TetrisGame
{
private: // Private fields
	// Tetris Game important information
	Tetromino* currentPiece = nullptr;
	Tetromino* nextPiece = nullptr;
	short level;
	int score;
	bool paused;
	bool pauseBuffered; // Pause buffer if you want one cycle to be paused
	PieceColor gameField[GAME::gameSize_X][GAME::gameSize_Y]; // It's only... colours? always has been.

#ifndef _DEBUG
private: // Private methods
#else // In debug we will put the functions public for unit testing
public:
#endif
	// Do not use these functions in the game. Tetris class will call them
	bool CheckValidMove(CoordinateSet moveVec) const;	// Checks a set of moves from the current piece
	bool CheckValidMove(MoveDirection dir) const;		// Used for player input that isn't a rotation
	int CalculatePoints(size_t const RowCount) const;
	void DeleteAndMoveDownRows(std::vector<int> const& rowNumbers); // Deletes the row numbers and moves top row down
	int GenRandomNumber();
#ifndef _DEBUG
private:
#else // In debug we will put the functions public for unit testing
public:
#endif
	bool TranslateInitPosToGamePos(PiecePosition const& pos) {}; // Returns false when init position cannot be done -> game is lost
	
	bool CheckHitBottom() const; // If the auto or force move down would result in the piece stopping return true
	void CheckForTetrisAndProcess();
	bool MovePiece(CoordinateSet moveVec);
	//void SetDownPiece(); // Only call when you know the spot is free else you will overwrite old locations
public:
	bool MovePiece(MoveDirection dir); // Player input and game loop
	bool RotateCurrentPiece();

	void InitNewPiece();
public:
	TetrisGame();
	~TetrisGame();

	void GameLoop(); // Move down called when 
};