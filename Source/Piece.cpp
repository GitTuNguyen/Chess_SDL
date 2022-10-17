#include "Piece.h"

void Piece::SetName(CellType i_name)
{
	m_name = i_name;
}

void Piece::SetColor(Color i_color)
{
	m_color = i_color;
}

CellType Piece::GetName()
{
	return m_name;
}

Color Piece::GetColor() 
{
	return m_color;
}
