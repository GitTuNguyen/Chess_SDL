#pragma once
#include "Piece.h"

class Castle : public Piece {
public:
	Castle();
	Castle(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** i_boardData) override;
private:

};