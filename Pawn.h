#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn();
	Pawn(Color i_color);
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:

};