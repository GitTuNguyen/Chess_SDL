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
	GameResult getGameResult();
	void Move(Piece* i_CurrentPiece, int i_CurrentPieceX, int i_CurrentPieceY, int i_MoveX, int i_MoveY);
	void UpdateGameResult(Piece* i_CurrentPiece, CellType i_recentKillPiece, int i_MoveX, int i_MoveY);
	~Board();
private:
	Piece* AddPiece(CellType i_name, Color i_color);
	Piece*** m_boardData;
	GameResult m_gameResult;
};