#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight();
	Knight(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** boardData) override;
private:

};