#pragma once
#include "Piece.h"

class Castle : public Piece {
public:
	Castle();
	Castle(Color i_color);
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:

};