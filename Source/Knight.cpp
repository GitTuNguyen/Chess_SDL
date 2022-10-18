#include "Knight.h"

Knight::Knight()
{
	SetName(PieceType::KNIGHT);
}

Knight::Knight(Color i_color)
{
	SetName(PieceType::KNIGHT);
	SetColor(i_color);
}
std::vector<Coordinate> Knight::AvailableMove(Piece*** boardData)
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
				if (boardData[availableMove.row][availableMove.col] == nullptr || boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (m_coordinate.col + (3 - i) < BOARD_WIDTH)
			{
				availableMove.col = m_coordinate.col + (3 - i);
				if (boardData[availableMove.row][availableMove.col] == nullptr || boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
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
				if (boardData[availableMove.row][availableMove.col] == nullptr || boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (m_coordinate.col + (3 - i) < BOARD_WIDTH)
			{
				availableMove.col = m_coordinate.col + (3 - i);
				if (boardData[availableMove.row][availableMove.col] == nullptr || boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}

		}
	}
	return move;
}