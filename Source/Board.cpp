
#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Castle.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"

Board::Board() :
	m_isBoardInitialized(false),
	m_hasPawnPromotion(false)
{
	Reset();
}

void Board::CreatePiece(PieceType i_name, Color i_color, Coordinate i_coordinate)
{
	Piece* piece = nullptr;
	switch (i_name)
	{
	case KING:
		piece = new King(i_color);
		break;
	case QUEEN:
		piece = new Queen(i_color);
		break;
	case BISHOP:
		piece = new Bishop(i_color);
		break;
	case CASTLE:
		piece = new Castle(i_color);
		break;
	case KNIGHT:
		piece = new Knight(i_color);
		break;
	case PAWN:
		piece = new Pawn(i_color);
		break;
	case NONE:
		break;
	default:
		break;
	}
	piece->SetCoordinate(i_coordinate);
	m_boardData[i_coordinate.row][i_coordinate.col] = piece;
}

void Board::Reset()
{
	if (!m_isBoardInitialized)
	{
		m_boardData = (Piece***)malloc(sizeof(Piece**) * BOARD_HEIGHT);
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			m_boardData[i] = (Piece**)malloc(sizeof(Piece*) * BOARD_WIDTH);
			memset(m_boardData[i], 0, sizeof(Piece*) * BOARD_WIDTH);
		}
		m_isBoardInitialized = true;
	}
	else {
		for (int i = 0; i < BOARD_HEIGHT; i++)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				RemovePiece(i, j);
			}
		}
	}

	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		CreatePiece(PieceType::PAWN, Color::BLACK, Coordinate(1, i));
		CreatePiece(PieceType::PAWN, Color::WHITE, Coordinate(6, i));
	}
	std::vector<PieceType> pieceArray = { PieceType::CASTLE, PieceType::KNIGHT, PieceType::BISHOP };
	for (int i = 0; i < pieceArray.size(); i++)
	{
		CreatePiece(pieceArray[i], Color::BLACK, Coordinate(0, i));
		CreatePiece(pieceArray[i], Color::BLACK, Coordinate(0, 7 - i));
		CreatePiece(pieceArray[i], Color::WHITE, Coordinate(7, i));
		CreatePiece(pieceArray[i], Color::WHITE, Coordinate(7, 7 - i));
	}
	CreatePiece(PieceType::KING, Color::BLACK, Coordinate(0, 3));
	CreatePiece(PieceType::QUEEN, Color::BLACK, Coordinate(0, 4));
	CreatePiece(PieceType::KING, Color::WHITE, Coordinate(7, 4));
	CreatePiece(PieceType::QUEEN, Color::WHITE, Coordinate(7, 3));

	m_gameResult = GameResult::RUNNING;
	m_selectedPiece = nullptr;
	m_currentPlayer = Color::WHITE;
}

Piece*** Board::GetBoardData()
{
	return m_boardData;
}


GameResult Board::GetGameResult()
{
	return m_gameResult;
}

void Board::UpdateGameResult(PieceType i_recentKillPiece)
{
	if (i_recentKillPiece == PieceType::KING)
	{
		if (m_selectedPiece->GetColor() == Color::WHITE)
		{
			m_gameResult = GameResult::WHITE_WIN;
		}
		else
		{
			m_gameResult = GameResult::BLACK_WIN;
		}
	}
}

Piece* Board::GetSelectedPiece()
{
	return m_selectedPiece;
}

std::vector<Coordinate> Board::GetCurrentAvailableMove()
{
	return m_selectedPiece->AvailableMove(m_boardData);
}

bool Board::CheckValidMove(int i_row, int i_col)
{
	std::vector<Coordinate> availableMove = GetCurrentAvailableMove();
	for (int i = 0; i < availableMove.size(); i++)
	{
		if (availableMove[i].row == i_row && availableMove[i].col == i_col)
		{
			return true;
		}
	}
	return false;
}

void Board::NextPlayerTurn()
{
	m_currentPlayer = m_currentPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;
	m_selectedPiece = nullptr;
}

void Board::RemovePiece(int i_row, int i_col)
{
	delete m_boardData[i_row][i_col];
	m_boardData[i_row][i_col] = nullptr;
}

void Board::Move(int i_targetRow, int i_targetCol)
{
	PieceType recentKilledPiece = PieceType::NONE;
	if (m_boardData[i_targetRow][i_targetCol] != nullptr)
	{
		recentKilledPiece = m_boardData[i_targetRow][i_targetCol]->GetName();
		RemovePiece(i_targetRow, i_targetCol);
	}

	int selectedX = m_selectedPiece->GetCoordinate().row;
	int selectedY = m_selectedPiece->GetCoordinate().col;

	m_boardData[i_targetRow][i_targetCol] = m_selectedPiece;
	m_boardData[i_targetRow][i_targetCol]->SetCoordinate(Coordinate(i_targetRow, i_targetCol));
	m_boardData[selectedX][selectedY] = nullptr;
	
	UpdateGameResult(recentKilledPiece);
	if (m_gameResult == RUNNING)
	{
		if (m_selectedPiece->GetName() == PieceType::PAWN)
		{
			if (m_selectedPiece->GetCoordinate().row == 0 || m_selectedPiece->GetCoordinate().row == BOARD_HEIGHT - 1)
			{
				m_hasPawnPromotion = true;
			}
		}
		
		if (!HasPawnPromotion())
		{
			NextPlayerTurn();
		}
	}
}

bool Board::HasPawnPromotion()
{
	return m_hasPawnPromotion;
}

void Board::CheckPawnPromotion(int i_selectedRow, int i_selectedCol)
{
	PieceType selectedPromotion = PieceType::NONE;
	if (m_selectedPiece->GetCoordinate().row == 0)
	{
		if ((m_selectedPiece->GetCoordinate().col == 0 && i_selectedCol == m_selectedPiece->GetCoordinate().col + 1)
			|| (m_selectedPiece->GetCoordinate().col > 0 && i_selectedCol == m_selectedPiece->GetCoordinate().col - 1))
		{
			if (i_selectedRow == 0)
			{
				selectedPromotion = PieceType::QUEEN;
			}
			else if (i_selectedRow == 1)
			{
				selectedPromotion = PieceType::KNIGHT;
			}
			else if (i_selectedRow == 2)
			{
				selectedPromotion = PieceType::CASTLE;
			}
			else if (i_selectedRow == 3)
			{
				selectedPromotion = PieceType::BISHOP;
			}
		}
	}
	else if (m_selectedPiece->GetCoordinate().row == BOARD_HEIGHT - 1)
	{
		if ((m_selectedPiece->GetCoordinate().col == 0 && i_selectedCol == m_selectedPiece->GetCoordinate().col + 1)
			|| (m_selectedPiece->GetCoordinate().col > 0 && i_selectedCol == m_selectedPiece->GetCoordinate().col - 1))
		{
			if (i_selectedRow == BOARD_HEIGHT - 4)
			{
				selectedPromotion = PieceType::QUEEN;
			}
			else if (i_selectedRow == BOARD_HEIGHT - 3)
			{
				selectedPromotion = PieceType::KNIGHT;
			}
			else if (i_selectedRow == BOARD_HEIGHT - 2)
			{
				selectedPromotion = PieceType::CASTLE;
			}
			else if (i_selectedRow == BOARD_HEIGHT - 1)
			{
				selectedPromotion = PieceType::BISHOP;
			}			
		}
	}

	if (selectedPromotion != PieceType::NONE)
	{
		PromotionPawn(selectedPromotion);
	}
}

void Board::PromotionPawn(PieceType i_piece)
{
	Coordinate pieceCoord = m_selectedPiece->GetCoordinate();
	Color pieceColor = m_selectedPiece->GetColor();
	RemovePiece(pieceCoord.row, pieceCoord.col);
	CreatePiece(i_piece, pieceColor, pieceCoord);
	NextPlayerTurn();
	m_hasPawnPromotion = false;
}

void Board::SetSelectedPiece(int i_row, int i_col)
{	
	m_selectedPiece = m_boardData[i_row][i_col];
}

Color Board::GetCurrentPlayer()
{
	return m_currentPlayer;
}

Board::~Board()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			delete m_boardData[i][j];
		}
	}
}