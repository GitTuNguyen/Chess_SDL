#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen();
	Queen(Color i_color);
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:

};