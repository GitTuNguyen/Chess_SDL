#include "King.h"

King::King()
{
	SetName(PieceType::KING);
}

King::King(Color i_color)
{
	SetName(PieceType::KING);
	SetColor(i_color);
}
std::vector<Coordinate> King::AvailableMove(Piece*** boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;

	for (int x = m_coordinate.row - 1; x <= m_coordinate.row + 1; x++)
	{
		for (int y = m_coordinate.col - 1; y <= m_coordinate.col + 1; y++)
		{
			if (x >= 0 && x < BOARD_HEIGHT && y >= 0 && y < BOARD_WIDTH && (x != m_coordinate.row || y != m_coordinate.col) && (boardData[x][y] == nullptr || boardData[x][y]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0))
			{
				availableMove.row = x;
				availableMove.col = y;
				move.push_back(availableMove);
			}
		}
	}
	return move;
}