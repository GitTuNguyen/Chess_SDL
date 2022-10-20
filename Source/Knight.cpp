#include "Knight.h"

Knight::Knight()
{
	m_type = PieceType::KNIGHT;
}

Knight::Knight(Color i_color)
{
	m_type = PieceType::KNIGHT;
	m_color = i_color;
}
std::vector<Coordinate> Knight::AvailableMove(Piece*** i_boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;
	for (int i = 1; i <= 2; i++)
	{
		if (m_coordinate.row - i >= 0)
		{
			availableMove.row = m_coordinate.row - i;
			if (m_coordinate.col - (3 - i) >= 0)
			{
				availableMove.col = m_coordinate.col - (3 - i);
				if (i_boardData[availableMove.row][availableMove.col] == nullptr || i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (m_coordinate.col + (3 - i) < BOARD_WIDTH)
			{
				availableMove.col = m_coordinate.col + (3 - i);
				if (i_boardData[availableMove.row][availableMove.col] == nullptr || i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}

		}
		if (m_coordinate.row + i < BOARD_HEIGHT)
		{
			availableMove.row = m_coordinate.row + i;
			if (m_coordinate.col - (3 - i) >= 0)
			{
				availableMove.col = m_coordinate.col - (3 - i);
				if (i_boardData[availableMove.row][availableMove.col] == nullptr || i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (m_coordinate.col + (3 - i) < BOARD_WIDTH)
			{
				availableMove.col = m_coordinate.col + (3 - i);
				if (i_boardData[availableMove.row][availableMove.col] == nullptr || i_boardData[availableMove.row][availableMove.col]->GetColor() + i_boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}

		}
	}
	return move;
}