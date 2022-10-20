#include "Castle.h"
Castle::Castle()
{
	m_type = PieceType::CASTLE;
}

Castle::Castle(Color i_color)
{
	m_type = PieceType::CASTLE;
	m_color = i_color;
}
std::vector<Coordinate> Castle::AvailableMove(Piece*** i_boardData)
{
	std::vector<Coordinate> moves;
	GetAvailableMoveByDirection(k_directionLeft, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionUp, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionDown, i_boardData, moves);
	GetAvailableMoveByDirection(k_directionRight, i_boardData, moves);
	return moves;
}