#include "Piece.h"

PieceType Piece::GetType()
{
	return m_type;
}

Color Piece::GetColor() 
{
	return m_color;
}

void Piece::SetCoordinate(Coordinate i_coordinate)
{
	m_coordinate = i_coordinate;
}

Coordinate Piece::GetCoordinate()
{
	return m_coordinate;
}
void Piece::GetAvailableMoveByDirection(Direction i_direction, Piece*** i_boardData, std::vector<Coordinate>& o_availableMove)
{
	Coordinate availableMove;
	for (int i = 1; ; i++)
	{
		availableMove.row = m_coordinate.row + (i * i_direction.x);
		availableMove.col = m_coordinate.col + (i * i_direction.y);
		if (availableMove.row < 0 || availableMove.row >= BOARD_HEIGHT
			|| availableMove.col < 0 || availableMove.col >= BOARD_WIDTH)
		{
			return;
		}
		if (i_boardData[availableMove.row][availableMove.col] == nullptr)
		{
			o_availableMove.push_back(availableMove);
		}
		else if (i_boardData[availableMove.row][availableMove.col]->GetColor() != i_boardData[m_coordinate.row][m_coordinate.col]->GetColor())
		{
			o_availableMove.push_back(availableMove);
			break;
		}
		else break;
	}
}

