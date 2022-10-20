#include "Pawn.h"
Pawn::Pawn()
{
	m_type = PieceType::PAWN;
}

Pawn::Pawn(Color i_color)
{
	m_type = PieceType::PAWN;
	m_color = i_color;
}

std::vector<Coordinate> Pawn::AvailableMove(Piece*** i_boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;
	availableMove.col = m_coordinate.col;
	switch (i_boardData[m_coordinate.row][m_coordinate.col]->GetColor())
	{
	case Color::BLACK:
		if (m_coordinate.row + 1 < BOARD_HEIGHT)
		{
			availableMove.row = m_coordinate.row + 1;
			if (i_boardData[availableMove.row][availableMove.col] == nullptr)
			{
				move.push_back(availableMove);
				if (m_coordinate.row == 1 && i_boardData[m_coordinate.row + 2][availableMove.col] == nullptr)
				{
					availableMove.row = m_coordinate.row + 2;
					move.push_back(availableMove);
					availableMove.row = m_coordinate.row + 1;
				}
			}
			if (m_coordinate.col - 1 >= 0)
			{
				availableMove.col = m_coordinate.col - 1;
				if (i_boardData[availableMove.row][availableMove.col] != nullptr && i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (m_coordinate.col + 1 < BOARD_WIDTH)
			{
				availableMove.col = m_coordinate.col + 1;
				if (i_boardData[availableMove.row][availableMove.col] != nullptr && i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
		}
		break;
	case Color::WHITE:
		if (m_coordinate.row - 1 >= 0)
		{
			availableMove.row = m_coordinate.row - 1;
			if (i_boardData[availableMove.row][availableMove.col] == nullptr)
			{
				move.push_back(availableMove);
				if (m_coordinate.row == 6 && i_boardData[m_coordinate.row - 2][availableMove.col] == nullptr)
				{
					availableMove.row = m_coordinate.row - 2;
					move.push_back(availableMove);
					availableMove.row = m_coordinate.row - 1;
				}
			}
			if (m_coordinate.col - 1 >= 0)
			{
				availableMove.col = m_coordinate.col - 1;
				if (i_boardData[availableMove.row][availableMove.col] != nullptr && i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (m_coordinate.col + 1 < BOARD_WIDTH)
			{
				availableMove.col = m_coordinate.col + 1;
				if (i_boardData[availableMove.row][availableMove.col] != nullptr && i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
		}
		break;
	default:
		break;
	}
	return move;
}