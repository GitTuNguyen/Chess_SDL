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
	std::vector<std::string> gameTextures = { "KingB", "KingW", "QueenB", "QueenW", "BishopB", "BishopW", "KnightB", "KnightW", "CastleB", "CastleW", "PawnB", "PawnW", "B_win", "W_win", "Chess_Stone", "YES", "NO"};
	for (int i = 0; i < gameTextures.size(); i++)
	{
		m_renderer->LoadTexture(gameTextures[i]);
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
				m_renderer->DrawCell(boardData[i][j]->GetName(), boardData[i][j]->GetColor(), j * CELL_SIZE, i * CELL_SIZE);
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
	case White_Player_WIN:
		gameResultString = "White Player WIN";
		break;
	case Black_Player_WIN:
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
			if (gameResult == GameResult::RUNNING)
			{
				Piece*** boardData = m_board->GetBoardData();
				if (!m_board->CheckPawnPromotion())
				{
					int clickedRow = (mouseY - TOP_EDGE) / CELL_SIZE;
					int clickedCol = (mouseX - LEFT_EDGE) / CELL_SIZE;
					if (boardData[clickedRow][clickedCol] != nullptr && boardData[clickedRow][clickedCol]->GetColor() == m_board->GetCurrentPlayer())
					{
						m_board->SetSelectedPiece(clickedRow, clickedCol);
					}
					else if (m_board->GetSelectedPiece() != nullptr && m_board->CheckValidMove(clickedRow, clickedCol))
					{
						m_board->UpdateMove(clickedRow, clickedCol);
					}
				}
				else {
					m_board->PromotionPawn(m_board->PawnPromotionCoordinate().x, m_board->PawnPromotionCoordinate().y, (mouseY - LEFT_EDGE) / CELL_SIZE, (mouseX - LEFT_EDGE) / CELL_SIZE);
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
		hasPawnPromotion = m_board->CheckPawnPromotion();
		isGameOver = gameResult != GameResult::RUNNING;
		m_renderer->PreRendering();
		m_renderer->DrawTable();
		if (m_board->GetSelectedPiece() != nullptr)
		{
			m_renderer->DrawAvailableMove(m_board->GetSelectedPieceCoordinate().x, m_board->GetSelectedPieceCoordinate().y, m_board->SelectedPieceAvailableMove());
		}
		DrawBoard();
		if (hasPawnPromotion)
		{
			m_renderer->DrawPromotionPawn(m_board->PawnPromotionCoordinate().x, m_board->PawnPromotionCoordinate().y);
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

