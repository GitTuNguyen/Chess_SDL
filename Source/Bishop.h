#pragma once
#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop();
	Bishop(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** i_boardData) override;
private:

};