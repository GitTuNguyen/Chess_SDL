#pragma once
#include <vector>
#include "GameDefinition.h"

class Piece {
public:
	void SetName(PieceType i_name);
	void SetColor(Color i_color);
	void SetCoordinate(Coordinate i_coordinate);	
	PieceType GetName();
	Color GetColor();
	Coordinate GetCoordinate();
	virtual std::vector<Coordinate> AvailableMove(Piece*** boardData) = 0;
protected:
	Coordinate m_coordinate;
private:
	PieceType m_name;
	Color m_color;
};