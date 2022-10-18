#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen();
	Queen(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** boardData) override;
private:

};