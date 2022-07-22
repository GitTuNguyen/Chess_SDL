#pragma once
#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop();
	Bishop(Color i_color);
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:

};