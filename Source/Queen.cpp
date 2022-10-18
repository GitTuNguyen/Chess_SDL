#include "Queen.h"

Queen::Queen()
{
	SetName(PieceType::QUEEN);
}

Queen::Queen(Color i_color)
{
	SetName(PieceType::QUEEN);
	SetColor(i_color);
}

std::vector<Coordinate> Queen::AvailableMove(Piece*** boardData)
{
	std::vector<Coordinate> move;
	Coordinate availableMove;
	for (int i = 1; m_coordinate.row + i < BOARD_HEIGHT; i++)
	{
		availableMove.row = m_coordinate.row + i;
		availableMove.col = m_coordinate.col;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.row - i >= 0; i++)
	{
		availableMove.row = m_coordinate.row - i;
		availableMove.col = m_coordinate.col;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.col - i >= 0; i++)
	{
		availableMove.row = m_coordinate.row;
		availableMove.col = m_coordinate.col - i;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.col + i < BOARD_WIDTH; i++)
	{
		availableMove.row = m_coordinate.row;
		availableMove.col = m_coordinate.col + i;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.row + i < BOARD_HEIGHT && m_coordinate.col + i < BOARD_WIDTH; i++)
	{
		availableMove.row = m_coordinate.row + i;
		availableMove.col = m_coordinate.col + i;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.row - i >= 0 && m_coordinate.col - i >= 0; i++)
	{
		availableMove.row = m_coordinate.row - i;
		availableMove.col = m_coordinate.col - i;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.row + i < BOARD_HEIGHT && m_coordinate.col - i >= 0; i++)
	{
		availableMove.row = m_coordinate.row + i;
		availableMove.col = m_coordinate.col - i;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	for (int i = 1; m_coordinate.row - i >= 0 && m_coordinate.col + i < BOARD_WIDTH; i++)
	{
		availableMove.row = m_coordinate.row - i;
		availableMove.col = m_coordinate.col + i;
		if (boardData[availableMove.row][availableMove.col] == nullptr)
		{
			move.push_back(availableMove);
		}
		else if (boardData[availableMove.row][availableMove.col]->GetColor() + boardData[m_coordinate.row][m_coordinate.col]->GetColor() == 0)
		{
			move.push_back(availableMove);
			break;
		}
		else break;
	}
	return move;
}