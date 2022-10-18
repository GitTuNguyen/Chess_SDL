#include "Piece.h"

void Piece::SetName(PieceType i_name)
{
	m_name = i_name;
}

void Piece::SetColor(Color i_color)
{
	m_color = i_color;
}

PieceType Piece::GetName()
{
	return m_name;
}

Color Piece::GetColor() 
{
	return m_color;
}

void Piece::SetCoordinate(Coordinate i_coordinate)
{
	m_coordinate = i_coordinate;
}

Coordinate Piece::GetCoordinate()
{
	return m_coordinate;
}
