#include "Game.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_inputManager = new InputManager();
	m_isPlayerWantExit = false;
	LoadPicture();
}

void Game::CreateNewGame()
{
	m_board->Reset();
	m_renderer->PreRendering();
	m_renderer->DrawTable();
	DrawBoard();
}

void Game::LoadPicture()
{
	std::vector<std::string> gameTextures = { "B_win", "W_win", "Chess_Stone", "YES", "NO"};
	for (int i = 0; i < gameTextures.size(); i++)
	{
		m_renderer->LoadTexture(gameTextures[i]);
	}
	std::vector<std::string> pieceTextures = { "KingB", "KingW", "QueenB", "QueenW", "BishopB", "BishopW", "KnightB", "KnightW", "CastleB", "CastleW", "PawnB", "PawnW" };
	for (int i = 0; i < pieceTextures.size(); i++)
	{
		PieceType pieceType = PieceType::NONE;
		std::string name = pieceTextures[i].substr(0, pieceTextures[i].size() - 1);
		if (name == "King")
		{
			pieceType = PieceType::KING;
		}
		else if (name == "Queen")
		{
			pieceType = PieceType::QUEEN;
		}
		else if (name == "Castle")
		{
			pieceType = PieceType::CASTLE;
		}
		else if (name == "Knight")
		{
			pieceType = PieceType::KNIGHT;
		}
		else if (name == "Bishop")
		{
			pieceType = PieceType::BISHOP;
		}
		else if (name == "Pawn")
		{
			pieceType = PieceType::PAWN;
		}
		char colorCode = pieceTextures[i].at(pieceTextures[i].size() - 1);
		Color pieceColor = colorCode == 'B' ? Color::BLACK : Color::WHITE;
		m_renderer->LoadPieceTexture(pieceTextures[i], pieceType, pieceColor);
	}
}

void Game::DrawBoard()
{
	Piece*** boardData = m_board->GetBoardData();
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (boardData[i][j] == nullptr)
			{
				continue;
			} else
			{
				m_renderer->DrawPiece(boardData[i][j]->GetName(), boardData[i][j]->GetColor(), j * CELL_SIZE, i * CELL_SIZE);
			}
		}
	}
}

void Game::DrawGameOverScreen()
{
	m_renderer->DrawGameOverPopup();
	std::string gameResultString;
	switch (m_board->GetGameResult())
	{
	case WHITE_WIN:
		gameResultString = "White Player WIN";
		break;
	case BLACK_WIN:
		gameResultString = "Black Player WIN";
		break;
	default:
		break;
	}
	m_renderer->DrawText(gameResultString, TEXT_SIZE, TEXT_GAME_RESULT_X, TEXT_GAME_RESULT_Y, TEXT_GAME_RESULT_HEIGHT, TEXT_GAME_RESULT_WIDTH);
}



void Game::Update()
{
	while (!m_isPlayerWantExit)
	{	
		int mouseX = 0;
		int mouseY = 0;
		bool isGameOver = false;
		m_inputManager->UpdateInput();
		m_isPlayerWantExit = m_inputManager->IsGoingToQuit();
		GameResult gameResult = m_board->GetGameResult();
		bool hasPawnPromotion = false;
		if (m_inputManager->IsMouseClick())
		{
			mouseX = m_inputManager->GetMouseX();
			mouseY = m_inputManager->GetMouseY();
			int clickedRow = (mouseY - TOP_EDGE) / CELL_SIZE;
			int clickedCol = (mouseX - LEFT_EDGE) / CELL_SIZE;
			if (gameResult == GameResult::RUNNING)
			{
				Piece*** boardData = m_board->GetBoardData();
				if (!m_board->HasPawnPromotion())
				{					
					if (boardData[clickedRow][clickedCol] != nullptr && boardData[clickedRow][clickedCol]->GetColor() == m_board->GetCurrentPlayer())
					{
						m_board->SetSelectedPiece(clickedRow, clickedCol);
					}
					else if (m_board->GetSelectedPiece() != nullptr && m_board->CheckValidMove(clickedRow, clickedCol))
					{
						m_board->Move(clickedRow, clickedCol);
					}
				}
				else {
					m_board->CheckPawnPromotion(clickedRow, clickedCol);
				}
			}
			else {
				if (mouseX >= YES_BUTTONL_X && mouseX <= YES_BUTTONL_X + YES_BUTTON_WIDTH && mouseY >= YES_BUTTON_Y && mouseY <= YES_BUTTON_Y + YES_BUTTON_HEIGHT)
				{
					CreateNewGame();
				}
				else if (mouseX >= NO_BUTTON_X && mouseX <= NO_BUTTON_X + NO_BUTTON_WIDTH && mouseY >= NO_BUTTON_Y && mouseY <= NO_BUTTON_Y + NO_BUTTON_HEIGHT) {
					m_isPlayerWantExit = true;
				}

			}
		}
		hasPawnPromotion = m_board->HasPawnPromotion();
		isGameOver = gameResult != GameResult::RUNNING;
		m_renderer->PreRendering();
		m_renderer->DrawTable();
		if (m_board->GetSelectedPiece() != nullptr)
		{
			m_renderer->DrawAvailableMove(m_board->GetSelectedPiece()->GetCoordinate(), m_board->GetCurrentAvailableMove());
		}
		DrawBoard();
		if (hasPawnPromotion)
		{
			m_renderer->DrawPromotionPawn(m_board->GetSelectedPiece()->GetCoordinate());
		}
		if (isGameOver)
		{
			DrawGameOverScreen();
		}
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}

Game::~Game()
{
	delete m_board;
	delete m_renderer;
	delete m_inputManager;
}

