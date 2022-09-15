#pragma once
#include "Board.h"
#include "Renderer.h"
#include <iostream>
#include "ConstValue.h"
class Game {
public:
	Game();
	void Update();
	~Game();
private:
	void LoadPicture();
	void DrawBoard();
	void CreateNewGame();
	bool CheckValidMove(int i_X, int i_Y);
	void UpdateMove(int i_MoveX, int i_MoveY);
	void Rematch();
	void setCurrentPiece(int i_X, int i_Y);
	bool CheckPawnPromotion(Piece*** i_boardData);
	Coordinate PawnPromotionCoordinate;
	std::vector<Coordinate> CurrentAvailableMove();
	Board* m_board;
	Renderer* m_renderer;
	Piece* m_currentPiece;
	Color m_currentPlayer;
	Coordinate m_currentPieceCoordinate;
	bool m_isPlayerWantExit;
	SDL_Event mainEvent;
};