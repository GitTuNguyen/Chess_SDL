
#include "Board.h"


Board::Board()
{
	Reset();

}
Piece* Board::AddPiece(CellType i_name, Color i_color)
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
	return piece;
}
void Board::Reset()
{
	m_boardData = (Piece***)malloc(sizeof(Piece**) * BOARD_HEIGHT);
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		m_boardData[i] = (Piece**)malloc(sizeof(Piece*) * BOARD_WIDTH);
	}
	
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (i == 1)
			{
				m_boardData[i][j] = AddPiece(CellType::PAWN, Color::BLACK);
			} 
			else if (i == 6)
			{
				m_boardData[i][j] = AddPiece(CellType::PAWN, Color::WHITE);
			}
			else if (i == 0)
			{
				if (j == 0 || j == 7)
				{
					m_boardData[i][j] = AddPiece(CellType::CASTLE, Color::BLACK);
				} 
				else if (j == 1 || j == 6)
				{
					m_boardData[i][j] = AddPiece(CellType::KNIGHT, Color::BLACK);
				}
				else if (j == 2 || j == 5)
				{
					m_boardData[i][j] = AddPiece(CellType::BISHOP, Color::BLACK);
				}
				else if (j == 3)
				{
					m_boardData[i][j] = AddPiece(CellType::KING, Color::BLACK);
				}
				else if (j == 4)
				{
					m_boardData[i][j] = AddPiece(CellType::QUEEN, Color::BLACK);
				}
			}
			else if (i == 7)
			{
				if (j == 0 || j == 7)
				{
					m_boardData[i][j] = AddPiece(CellType::CASTLE, Color::WHITE);
				}
				else if (j == 1 || j == 6)
				{
					m_boardData[i][j] = AddPiece(CellType::KNIGHT, Color::WHITE);
				}
				else if (j == 2 || j == 5)
				{
					m_boardData[i][j] = AddPiece(CellType::BISHOP, Color::WHITE);
				}
				else if (j == 3)
				{
					m_boardData[i][j] = AddPiece(CellType::QUEEN, Color::WHITE);
				}
				else if (j == 4)
				{
					m_boardData[i][j] = AddPiece(CellType::KING, Color::WHITE);
				}
			}
			else {
				m_boardData[i][j] = nullptr;
			}
		}
	}
	m_gameResult = GameResult::RUNNING;
}

Piece*** Board::getBoardData()
{
	return m_boardData;
}


GameResult Board::getGameResult()
{
	return m_gameResult;
}



void Board::UpdateGameResult(Piece* i_CurrentPiece, CellType i_recentKillPiece, int i_MoveX, int i_MoveY)
{
	if (i_recentKillPiece == CellType::KING)
	{
		if (i_CurrentPiece->getColor() == Color::WHITE)
		{
			m_gameResult = GameResult::White_Player_WIN;
		}
		else
		{
			m_gameResult = GameResult::Black_Player_WIN;
		}
	}
}

void Board::Move(Piece* i_CurrentPiece, int i_CurrentPieceX, int i_CurrentPieceY, int i_MoveX, int i_MoveY)
{
	CellType recentKillPiece = CellType::NONE;
	if (m_boardData[i_MoveX][i_MoveY] != nullptr)
	{
		recentKillPiece = m_boardData[i_MoveX][i_MoveY]->getName();
	}
	m_boardData[i_MoveX][i_MoveY] = i_CurrentPiece;
	m_boardData[i_CurrentPieceX][i_CurrentPieceY] = nullptr;
	UpdateGameResult(i_CurrentPiece, recentKillPiece, i_MoveX, i_MoveY);
}

void Board::PromotionPawn(int i_PawnX, int i_PawnY, int i_mouseX,int  i_mouseY)
{
	if (i_PawnX == 0)
	{
		if ((i_PawnY == 0 && i_mouseY == i_PawnY + 1) || (i_PawnY > 0 && i_mouseY == i_PawnY - 1) )
		{
			if (i_mouseX == 0)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::QUEEN, Color::WHITE);
			}
			else if (i_mouseX == 1)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::KNIGHT, Color::WHITE);
			}
			else if (i_mouseX == 2)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::CASTLE, Color::WHITE);
			}
			else if (i_mouseX == 3)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::BISHOP, Color::WHITE);
			}
		}
	}
	else if (i_PawnX == BOARD_HEIGHT - 1)
	{
		if ((i_PawnY == 0 && i_mouseY == i_PawnY + 1) || (i_PawnY > 0 && i_mouseY == i_PawnY - 1))
		{
			if (i_mouseX == BOARD_HEIGHT - 4)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::QUEEN, Color::BLACK);
			}
			else if (i_mouseX == BOARD_HEIGHT - 3)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::KNIGHT, Color::BLACK);
			}
			else if (i_mouseX == BOARD_HEIGHT - 2)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::CASTLE, Color::BLACK);
			}
			else if (i_mouseX == BOARD_HEIGHT - 1)
			{
				m_boardData[i_PawnX][i_PawnY] = AddPiece(CellType::BISHOP, Color::BLACK);
			}
		}
	}
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