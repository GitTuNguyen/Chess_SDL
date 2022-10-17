#pragma once
#include <vector>
#include "GameDefinition.h"

class Piece {
public:
	void SetName(CellType i_name);
	void SetColor(Color i_color);
	CellType GetName();
	Color GetColor();
	virtual std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) = 0;
private:
	CellType m_name;
	Color m_color;	
};