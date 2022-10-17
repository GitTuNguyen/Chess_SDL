#pragma once
#include <cstdlib>
#include "King.h"
#include "Queen.h"
#include "Castle.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"

enum GameResult {
	RUNNING,
	White_Player_WIN,
	Black_Player_WIN
};
class Board {
public:
	Board();
	void Reset();
	Piece*** getBoardData();

	void SetSelectedPiece(int i_X, int i_Y);
	Piece* GetSelectedPiece();
	std::vector<Coordinate> SelectedPieceAvailableMove();
	Coordinate GetSelectedPieceCoordinate();

	Coordinate PawnPromotionCoordinate();
	bool CheckPawnPromotion();
	void PromotionPawn(int i_PawnX, int i_PawnY, int i_mouseX, int i_mouseY);

	bool CheckValidMove(int i_X, int i_Y);
	void Move(Piece* i_CurrentPiece, int i_CurrentPieceX, int i_CurrentPieceY, int i_MoveX, int i_MoveY);
	void UpdateMove(int i_moveX, int i_moveY);

	void UpdateGameResult(Piece* i_CurrentPiece, CellType i_recentKillPiece, int i_MoveX, int i_MoveY);
	GameResult getGameResult();

	Color GetCurrentPlayer();

	~Board();
private:
	Piece* AddPiece(CellType i_name, Color i_color);
	Piece*** m_boardData;
	GameResult m_gameResult;
	Piece* m_selectedPiece;
	Coordinate m_selectedPieceCoordinate;
	Coordinate m_pawnPromotionCoordinate;
	Color m_currentPlayer;

};