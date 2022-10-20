#pragma once
#include <vector>
#include "GameDefinition.h"

struct Direction {
	int x, y;
	Direction() {}
	Direction(int i_x, int i_y) :
		x(i_x),
		y(i_y)
	{}
};

const Direction k_directionLeft = Direction(0, -1);
const Direction k_directionRight = Direction(0, 1);
const Direction k_directionUp = Direction(-1, 0);
const Direction k_directionDown = Direction(1, 0);
const Direction k_directionUpLeft = Direction(-1, -1);
const Direction k_directionUpRight = Direction(-1, 1);
const Direction k_directionDownLeft = Direction(1, -1);
const Direction k_directionDownRight = Direction(1, 1);

class Piece {

public:
	void SetCoordinate(Coordinate i_coordinate);	
	PieceType GetType();
	Color GetColor();
	Coordinate GetCoordinate();
	void GetAvailableMoveByDirection(Direction i_direction, Piece*** i_boardData, std::vector<Coordinate>& o_availableMove);
	virtual std::vector<Coordinate> AvailableMove(Piece*** i_boardData) = 0;
protected:
	Coordinate m_coordinate;
	PieceType m_type;
	Color m_color;
};