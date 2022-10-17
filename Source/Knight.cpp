#include "Knight.h"

Knight::Knight()
{
	SetName(CellType::KNIGHT);
}

Knight::Knight(Color i_color)
{
	SetName(CellType::KNIGHT);
	SetColor(i_color);
}
std::vector<Coordinate> Knight::AvailableMove(int i_X, int i_Y, Piece*** boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;
	for (int i = 1; i <= 2; i++)
	{
		if (i_X - i >= 0)
		{
			availableMove.x = i_X - i;
			if (i_Y - (3 - i) >= 0)
			{
				availableMove.y = i_Y - (3 - i);
				if (boardData[availableMove.x][availableMove.y] == nullptr || boardData[availableMove.x][availableMove.y]->GetColor() + boardData[i_X][i_Y]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (i_Y + (3 - i) < BOARD_WIDTH)
			{
				availableMove.y = i_Y + (3 - i);
				if (boardData[availableMove.x][availableMove.y] == nullptr || boardData[availableMove.x][availableMove.y]->GetColor() + boardData[i_X][i_Y]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}

		}
		if (i_X + i < BOARD_HEIGHT)
		{
			availableMove.x = i_X + i;
			if (i_Y - (3 - i) >= 0)
			{
				availableMove.y = i_Y - (3 - i);
				if (boardData[availableMove.x][availableMove.y] == nullptr || boardData[availableMove.x][availableMove.y]->GetColor() + boardData[i_X][i_Y]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (i_Y + (3 - i) < BOARD_WIDTH)
			{
				availableMove.y = i_Y + (3 - i);
				if (boardData[availableMove.x][availableMove.y] == nullptr || boardData[availableMove.x][availableMove.y]->GetColor() + boardData[i_X][i_Y]->GetColor() == 0)
				{
					move.push_back(availableMove);
				}
			}

		}
	}
	return move;
}