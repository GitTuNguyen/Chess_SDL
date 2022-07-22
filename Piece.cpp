#include "Piece.h"

void Piece::setName(CellType i_name)
{
	m_name = i_name;
}

void Piece::setColor(Color i_color)
{
	m_color = i_color;
}

CellType Piece::getName()
{
	return m_name;
}

Color Piece::getColor() 
{
	return m_color;
}
