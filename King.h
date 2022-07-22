#pragma once
#include "Piece.h"

class Piece;

class King : public Piece 
{
public:
	King();
	King(Color i_color);
	std::vector<Coordinate> AvailableMove(int i_X, int i_Y, Piece*** boardData) override;
private:
};