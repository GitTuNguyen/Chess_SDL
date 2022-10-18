#pragma once
#include "Piece.h"

class Piece;

class King : public Piece 
{
public:
	King();
	King(Color i_color);
	std::vector<Coordinate> AvailableMove(Piece*** boardData) override;
private:
};