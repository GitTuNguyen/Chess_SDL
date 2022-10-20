#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn();
	Pawn(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** i_boardData) override;
private:

};