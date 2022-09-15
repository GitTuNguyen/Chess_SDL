#include "Castle.h"
Castle::Castle()
{
	setName(CellType::CASTLE);
}

Castle::Castle(Color i_color)
{
	setName(CellType::CASTLE);
	setColor(i_color);
}
std::vector<Coordinate> Castle::AvailableMove(int i_X, int i_Y, Piece*** boardData)
{
	
	std::vector<Coordinate> move;
	Coordinate availableMove;
	for (int i = 1; i_X + i < BOARD_HEIGHT; i++)
	{
		availableMove.x = i_X + i;
		availableMove.y = i_Y;
		if (boardData[availableMove.x][availableMove.y] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; i_X - i >= 0; i++)
	{
		availableMove.x = i_X - i;
		availableMove.y = i_Y;
		if (boardData[availableMove.x][availableMove.y] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; i_Y - i >= 0; i++)
	{
		availableMove.x = i_X;
		availableMove.y = i_Y - i;
		if (boardData[availableMove.x][availableMove.y] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; i_Y + i < BOARD_WIDTH; i++)
	{
		availableMove.x = i_X;
		availableMove.y = i_Y + i;
		if (boardData[availableMove.x][availableMove.y] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.x][availableMove.y]->getColor() + boardData[i_X][i_Y]->getColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	return move;
}