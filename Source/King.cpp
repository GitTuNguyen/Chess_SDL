#include "King.h"

King::King()
{
	SetName(CellType::KING);
}

King::King(Color i_color)
{
	SetName(CellType::KING);
	SetColor(i_color);
}
std::vector<Coordinate> King::AvailableMove(int i_X, int i_Y, Piece*** boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;

	for (int x = i_X - 1; x <= i_X + 1; x++)
	{
		for (int y = i_Y - 1; y <= i_Y + 1; y++)
		{
			if (x >= 0 && x < BOARD_HEIGHT && y >= 0 && y < BOARD_WIDTH && (x != i_X || y != i_Y) && (boardData[x][y] == nullptr || boardData[x][y]->GetColor() + boardData[i_X][i_Y]->GetColor() == 0))
			{
				availableMove.x = x;
				availableMove.y = y;
				move.push_back(availableMove);
			}
		}
	}
	return move;
}