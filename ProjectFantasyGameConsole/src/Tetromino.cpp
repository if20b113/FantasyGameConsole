#include "Tetromino.h"

inline Tetromino::Tetromino() { x_offset = GAME::gameSize_X % 2 == 0 ? (short)(float(GAME::gameSize_X) / 2.0f) : (short)(float(GAME::gameSize_X) / 2.0f + 1.0f); }

Tetromino::~Tetromino()
{
}

I_Piece::I_Piece()
{
	/* ROT_NORMAL			ROT_RIGHT				ROT_DOWN				ROT_LEFT
			* 1 2 3 4 O O O O O O	0 0 1 0 O O O O O O		0 0 0 0 O O O O O O		0 4 0 0 O O O O O O
			* O O O O O O O O O O	0 0 2 0 O O O O O O		4 3 2 1 O O O O O O		0 3 0 0 O O O O O O
			* O O O O O O O O O O	0 0 3 0 O O O O O O		0 0 0 0 O O O O O O		0 2 0 0 O O O O O O
			* O O O O O O O O O O	0 0 4 0 O O O O O O		0 0 0 0 O O O O O O		0 1 0 0 O O O O O O
			* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
			* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
			* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
			* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
			* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
			* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
			*/
	m_InitialPosition = { {short(x_offset+0),0}, {short(x_offset + 1),0}, {short(x_offset + 2),0}, {short(x_offset + 3),0} }; // Initial Positions
}

CoordinateSet I_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {2,0}, {1,1}, {0,2}, {-1,3} };
	case ROT_RIGHT:
		return CoordinateSet{ {1,1}, {0,0}, {-1,-1}, {-2,-2} };
	case ROT_DOWN:
		return CoordinateSet{ {1,-1}, {0,0}, {-1,1}, {-1,2} };
	case ROT_LEFT:
		return CoordinateSet{ {-1,-3}, {0,-2}, {1,-1}, {2,0} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}

J_Piece::J_Piece()
{
	/*
	Y0	* 1 O O O O O O O O O	0 2 1 0 O O O O O O		0 0 0 0 O O O O O O		0 4 0 0 O O O O O O
	Y1	* 2 3 4 O O O O O O O	0 3 0 0 O O O O O O		4 3 2 0 O O O O O O		0 3 0 0 O O O O O O
	Y2	* O O O O O O O O O O	0 4 0 0 O O O O O O		0 0 1 0 O O O O O O		1 2 0 0 O O O O O O
	Y3	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		*/
	m_InitialPosition = { {short(x_offset + 0),0}, {short(x_offset + 0),1}, {short(x_offset + 1),1}, {short(x_offset + 2),1} }; // Initial Positions
}

CoordinateSet J_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {2,0}, {1,-1}, {0,0}, {-1,1} };
	case ROT_RIGHT:
		return CoordinateSet{ {0,2}, {1,1}, {0,0}, {-1,-1} };
	case ROT_DOWN:
		return CoordinateSet{ {-2,0}, {-1,1}, {0,0}, {1,-1} };
	case ROT_LEFT:
		return CoordinateSet{ {0,-2}, {-1,-1}, {0,0}, {1,1} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}

L_Piece::L_Piece()
{
	/*
Y0	* O O 4 O O O O O O O	0 1 0 0 O O O O O O		0 0 0 0 O O O O O O		4 3 0 0 O O O O O O
Y1	* 1 2 3 O O O O O O O	0 2 0 0 O O O O O O		3 2 1 0 O O O O O O		0 2 0 0 O O O O O O
Y2	* O O O O O O O O O O	0 3 4 0 O O O O O O		4 0 0 0 O O O O O O		0 1 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	*/
	m_InitialPosition = { {short(x_offset + 0),1}, {short(x_offset + 1),1}, {short(x_offset + 2),1}, {short(x_offset + 2),0} }; // Initial Positions
}

CoordinateSet L_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {1,-1}, {0,0}, {-1,1}, {0,2} };
	case ROT_RIGHT:
		return CoordinateSet{ {1,1}, {0,0}, {-1,-1}, {-2,0} };
	case ROT_DOWN:
		return CoordinateSet{ {-1,1}, {0,0}, {1,-1}, {0,-2} };
	case ROT_LEFT:
		return CoordinateSet{ {-1,-1}, {0,0}, {1,1}, {2,0} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}

O_Piece::O_Piece()
{
	/*
	* O 1 2 O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O 3 4 O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	*/
	m_InitialPosition = { {short(x_offset + 1),0}, {short(x_offset + 2),0}, {short(x_offset + 1),1}, {short(x_offset + 2),1} }; // Initial Positions
}

CoordinateSet O_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
	case ROT_RIGHT:
		return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
	case ROT_DOWN:
		return CoordinateSet{ {0,0}, {0,0},{0,0}, {0,0} };
	case ROT_LEFT:
		return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}

S_Piece::S_Piece()
{		
	//X  
	/*
	Y0	* O 3 4 O O O O O O O	0 1 0 0 O O O O O O		0 0 0 0 O O O O O O		4 0 0 0 O O O O O O
	Y1	* 1 2 O O O O O O O O	0 2 3 0 O O O O O O		0 2 1 0 O O O O O O		3 2 0 0 O O O O O O
	Y2	* O O O O O O O O O O	0 0 4 0 O O O O O O		4 3 0 0 O O O O O O		0 1 0 0 O O O O O O
	Y3	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
		*/
	m_InitialPosition = { {short(x_offset + 0),1}, {short(x_offset + 1),1}, {short(x_offset + 1),0}, {short(x_offset + 2),0} }; // Initial Positions
}

CoordinateSet S_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {1,-1}, {0,0}, {1,1}, {0,2} };
	case ROT_RIGHT:
		return CoordinateSet{ {1,1}, {0,0}, {-1,1}, {-2,0} };
	case ROT_DOWN:
		return CoordinateSet{ {-1,1}, {0,0}, {-1,-1}, {0,-2} };
	case ROT_LEFT:
		return CoordinateSet{ {-1,-1}, {0,0}, {1,-1}, {2,0} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}

T_Piece::T_Piece()
{
	//X  
/*
Y0	* O 4 O O O O O O O O	0 1 0 0 O O O O O O		0 0 0 0 O O O O O O		0 3 0 0 O O O O O O
Y1	* 1 2 3 O O O O O O O	0 2 4 0 O O O O O O		3 2 1 0 O O O O O O		4 2 0 0 O O O O O O
Y2	* O O O O O O O O O O	0 3 0 0 O O O O O O		0 4 0 0 O O O O O O		0 1 0 0 O O O O O O
Y3	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	*/
	m_InitialPosition = { {short(x_offset + 0),1}, {short(x_offset + 1),1}, {short(x_offset + 2),1}, {short(x_offset + 1),0} }; // Initial Positions
}

CoordinateSet T_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {1,-1}, {0,0}, {-1,1}, {1,1} };
	case ROT_RIGHT:
		return CoordinateSet{ {1,1}, {0,0}, {-1,-1}, {-1,1} };
	case ROT_DOWN:
		return CoordinateSet{ {-1,1}, {0,0},{1,-1}, {-1,-1} };
	case ROT_LEFT:
		return CoordinateSet{ {-1,-1}, {0,0}, {1,1}, {1,-1} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}

Z_Piece::Z_Piece()
{
	//X  
	/*
Y0	* 1 2 O O O O O O O O	0 0 1 0 O O O O O O		0 0 0 0 O O O O O O		0 4 0 0 O O O O O O
Y1	* 0 3 4 O O O O O O O	0 3 2 0 O O O O O O		4 3 0 0 O O O O O O		2 3 0 0 O O O O O O
Y2	* O O O O O O O O O O	0 4 0 0 O O O O O O		0 2 1 0 O O O O O O		1 0 0 0 O O O O O O
Y3	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	* O O O O O O O O O O	0 0 0 0 O O O O O O		0 0 0 0 O O O O O O		0 0 0 0 O O O O O O
	*/
	m_InitialPosition = { {short(x_offset + 0),0}, {short(x_offset + 1),0}, {short(x_offset + 1),1}, {short(x_offset + 2),1} }; // Initial Positions
}

CoordinateSet Z_Piece::GetNextRotation() const
{
	switch (m_CurrRot)
	{
	case ROT_NORMAL:
		return CoordinateSet{ {2,0}, {1,1}, {0,0}, {-1,1} };
	case ROT_RIGHT:
		return CoordinateSet{ {0,-2}, {-1,1}, {0,0}, {-1,-1} };
	case ROT_DOWN:
		return CoordinateSet{ {-2,0}, {-1,-1},{0,0}, {1,-1} };
	case ROT_LEFT:
		return CoordinateSet{ {0,-2}, {1,-1}, {0,0}, {1,1} };
	}
	return CoordinateSet{ {0,0}, {0,0}, {0,0}, {0,0} };
}
