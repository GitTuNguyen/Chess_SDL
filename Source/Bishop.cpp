#include "Bishop.h"

Bishop::Bishop()
{
	m_type = PieceType::BISHOP;
}

Bishop::Bishop(Color i_color)
{
	m_type = PieceType::BISHOP;
	m_color = i_color;
}

std::vector<Coordinate> Bishop::AvailableMove(Piece*** i_boardData)
{
	std::vector<Coordinate> moves;
	GetAvailableMoveByDirection(k_directionDownLeft, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionUpLeft, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionDownRight, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionUpRight, i_boardData, moves);
	return moves;
}