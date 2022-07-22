#pragma once
#include "Piece.h"

class None : public Piece {
public:
	None();
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:

};