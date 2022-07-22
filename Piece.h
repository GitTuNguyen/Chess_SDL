#pragma once
#include <vector>
#include "ConstValue.h"

class Piece {
public:
	void setName(CellType i_name);
	void setColor(Color i_color);
	CellType getName();
	Color getColor();
	virtual std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) = 0;
private:
	CellType m_name;
	Color m_color;	
};