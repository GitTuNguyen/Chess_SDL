#include "Pawn.h"
Pawn::Pawn()
{
	setName(CellType::PAWN);
}

Pawn::Pawn(Color i_color)
{
	setName(CellType::PAWN);
	setColor(i_color);
}

std::vector<Coordinate> Pawn::AvailableMove(int i_X, int i_Y, Piece*** boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;
	availableMove.y = i_Y;
	switch (boardData[i_X][i_Y]->getColor())
	{
	case Color::BLACK:
		if (i_X + 1 < BOARD_HEIGHT)
		{
			availableMove.x = i_X + 1;
			if (boardData[availableMove.x][availableMove.y] == nullptr)
			{
				move.push_back(availableMove);
				if (i_X == 1 && boardData[i_X + 2][availableMove.y] == nullptr)
				{
					availableMove.x = i_X + 2;
					move.push_back(availableMove);
					availableMove.x = i_X + 1;
				}
			}
			if (i_Y - 1 >= 0)
			{
				availableMove.y = i_Y - 1;
				if (boardData[availableMove.x][availableMove.y] != nullptr && boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (i_Y + 1 < BOARD_WIDTH)
			{
				availableMove.y = i_Y + 1;
				if (boardData[availableMove.x][availableMove.y] != nullptr && boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
		}
		break;
	case Color::WHITE:
		if (i_X - 1 >= 0)
		{
			availableMove.x = i_X - 1;
			if (boardData[availableMove.x][availableMove.y] == nullptr)
			{
				move.push_back(availableMove);
				if (i_X == 6 && boardData[i_X - 2][availableMove.y] == nullptr)
				{
					availableMove.x = i_X - 2;
					move.push_back(availableMove);
					availableMove.x = i_X - 1;
				}
			}
			if (i_Y - 1 >= 0)
			{
				availableMove.y = i_Y - 1;
				if (boardData[availableMove.x][availableMove.y] != nullptr && boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
				{
					move.push_back(availableMove);
				}
			}
			if (i_Y + 1 < BOARD_WIDTH)
			{
				availableMove.y = i_Y + 1;
				if (boardData[availableMove.x][availableMove.y] != nullptr && boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
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