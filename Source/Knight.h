#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight();
	Knight(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** i_boardData) override;
private:

};