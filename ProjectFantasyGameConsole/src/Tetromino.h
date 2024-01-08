#pragma once
#include <vector>
#include "constants.h"

// Based on https://tetris.fandom.com/wiki/SRS


// Define pieces
struct PiecePosition // Defines the position of each individual renderable block.
	// One Tetromino has multiple piece positions.
	// The Shape determines where the PiecePositions are located.
{
	short sPos_x; // Integers are too large for our purpose.
	short sPos_y;
};

enum Rotation // What rotation am I in?
{
	ROT_NORMAL = 0,
	ROT_RIGHT,
	ROT_DOWN,
	ROT_LEFT
};

enum class PieceColor
{
	COLOR_BACKGROUND = 0,
	COLOR_BLUE,
	COLOR_DARKBLUE,
	COLOR_ORANGE,
	COLOR_YELLOW,
	COLOR_GREEN,
	COLOR_PINK,
	COLOR_RED,
};

typedef std::vector<PiecePosition> CoordinateSet;

class Tetromino // Abstract class that stores methods and info about them.
{	
protected:
	CoordinateSet m_InitialPosition{};
	CoordinateSet m_CurrPos{ {0,0}, {0,0}, {0,0}, {0,0} };
	PieceColor m_color;
	Rotation m_CurrRot = ROT_NORMAL;
	short x_offset;
public:
	Tetromino();
	virtual ~Tetromino();
	//virtual Rotation GetNextRotation() = 0;

	/*
	void MovePieceToCenter()
	{
		// Get middle position x-axis
		short x = GAME::gameSize_X % 2 == 0 ? (short)(float(GAME::gameSize_X) / 2.0f) : (short)(float(GAME::gameSize_X) / 2.0f + 1.0f);
		for (auto it : m_InitialPosition)
			it.sPos_x += x;
	}*/
	void SetCurrentPositions(CoordinateSet const& newPositions)						{ if (newPositions.size() != GAME::MAX_BLOCK_COUNT) return; m_CurrPos = newPositions; }
	void SetCurrentPositionsAt(PiecePosition const& newPosition, size_t const at)	{ if (at >= GAME::MAX_BLOCK_COUNT) return; m_CurrPos.at(at) = newPosition; }

	PieceColor GetColor() const				{ return m_color; }
	short GetXAt(size_t const at) const		{ return m_CurrPos.at(at).sPos_x; }
	short GetYAt(size_t const at) const		{ return m_CurrPos.at(at).sPos_y; }

	bool HavePosition(PiecePosition const& piecePos)
	{
		for (auto it : m_CurrPos)
			if (it.sPos_x == piecePos.sPos_x && it.sPos_y == piecePos.sPos_y)
				return true;
		return false;
	}
	virtual CoordinateSet GetNextRotation() const = 0; // Returns a differential CoordinateSet which addition to the current coordinates will result in the rotated coordinates
};

class I_Piece : public Tetromino
{
public:
	I_Piece();
	virtual CoordinateSet GetNextRotation() const;
};
class J_Piece : public Tetromino
{
public:
	J_Piece();
	virtual CoordinateSet GetNextRotation() const;
};
class L_Piece : public Tetromino
{
public:
	L_Piece();
	virtual CoordinateSet GetNextRotation() const;
};
class O_Piece : public Tetromino
{
public:
	O_Piece();
	virtual CoordinateSet GetNextRotation() const;
};
class S_Piece : public Tetromino
{
public:
	S_Piece();
	virtual CoordinateSet GetNextRotation() const;
};

class T_Piece : public Tetromino
{
public:
	T_Piece();
	virtual CoordinateSet GetNextRotation() const;
};
class Z_Piece : public Tetromino
{
public:
	Z_Piece();
	virtual CoordinateSet GetNextRotation() const;
};