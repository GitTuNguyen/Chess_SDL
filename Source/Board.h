#pragma once
#include "Piece.h"

enum GameResult {
	RUNNING,
	WHITE_WIN,
	BLACK_WIN
};
class Board {
public:
	Board();
	void Reset();
	Piece*** GetBoardData();

	void SetSelectedPiece(int i_row, int i_col);
	Piece* GetSelectedPiece();
	void UpdateCurrentAvailableMoves();
	std::vector<Coordinate> GetCurrentAvailableMove();
	
	void CheckPawnPromotion(int i_selectedRow, int i_selectedCol);
	bool HasPawnPromotion();
	
	bool CheckValidMove(int i_row, int i_col);
	void Move(int i_targetRow, int i_targeCol);

	void UpdateGameResult(PieceType i_recentKillPiece);
	GameResult GetGameResult();

	Color GetCurrentPlayer();


	~Board();
private:
	void CreatePiece(PieceType i_name, Color i_color, Coordinate i_coordinate);
	void RemovePiece(int i_row, int i_col);
	void PromotionPawn(PieceType i_piece);
	void NextPlayerTurn();
	Piece*** m_boardData;
	GameResult m_gameResult;
	Piece* m_selectedPiece;
	Color m_currentPlayer;
	bool m_isBoardInitialized;
	bool m_hasPawnPromotion;
	std::vector<Coordinate> m_currentAvailableMoves;
};