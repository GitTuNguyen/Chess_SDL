#include "Queen.h"

Queen::Queen()
{
	m_type = PieceType::QUEEN;
}

Queen::Queen(Color i_color)
{
	m_type = PieceType::QUEEN;
	m_color = i_color;
}

std::vector<Coordinate> Queen::AvailableMove(Piece*** i_boardData)
{
	std::vector<Coordinate> moves;
	GetAvailableMoveByDirection(k_directionDownLeft, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionUpLeft, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionDownRight, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionUpRight, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionLeft, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionUp, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionDown, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionRight, i_boardData, moves);
	return moves;
}