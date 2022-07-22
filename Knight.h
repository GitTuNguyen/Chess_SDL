#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight();
	Knight(Color i_color);
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:

};