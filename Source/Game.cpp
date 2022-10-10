#include "Game.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_inputManager = new InputManager();
	m_currentPlayer = Color::WHITE;
	m_isPlayerWantExit = false;
	m_currentPiece = nullptr;
	LoadPicture();
}

void Game::CreateNewGame()
{
	m_board->Reset();
	m_renderer->PreRendering();
	m_renderer->DrawTable();
	DrawBoard();
	m_currentPlayer = Color::WHITE;
}

void Game::LoadPicture()
{
	std::vector<std::string> gameTextures = { "KingB", "KingW", "QueenB", "QueenW", "BishopB", "BishopW", "KnightB", "KnightW", "CastleB", "CastleW", "PawnB", "PawnW", "CasaVerde", "CasaVerde_", "B_win", "W_win", "Chess_Stone", "YES", "NO"};
	for (int i = 0; i < gameTextures.size(); i++)
	{
		m_renderer->LoadTexture(gameTextures[i]);
	}
}

void Game::DrawBoard()
{
	Piece*** boardData = m_board->getBoardData();
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (boardData[i][j] == nullptr)
			{
				continue;
			} else
			{
				m_renderer->DrawCell(boardData[i][j]->getName(), boardData[i][j]->getColor(), j * SIZE_CELL_PIXEL, i * SIZE_CELL_PIXEL);
			}
		}
	}
}

void Game::setCurrentPiece(int i_X, int i_Y)
{
	Piece*** boardData = m_board->getBoardData();
	m_currentPiece = boardData[i_X][i_Y];
	m_currentPieceCoordinate.x = i_X;
	m_currentPieceCoordinate.y = i_Y;
}

std::vector<Coordinate> Game::CurrentAvailableMove()
{
	return m_currentPiece->AvailableMove(m_currentPieceCoordinate.x, m_currentPieceCoordinate.y, m_board->getBoardData());
}

bool Game::CheckValidMove(int i_X, int i_Y)
{
	std::vector<Coordinate> availableMove = CurrentAvailableMove();
	for (int i = 0; i < availableMove.size(); i++)
	{
		if (availableMove[i].x == i_X && availableMove[i].y == i_Y)
		{
			return true;
		}
	}
	return false;
}


void Game::UpdateMove(int i_MoveX, int i_MoveY)
{
	m_board->Move(m_currentPiece, m_currentPieceCoordinate.x, m_currentPieceCoordinate.y, i_MoveX, i_MoveY);
	m_currentPiece = nullptr;
	m_currentPlayer = m_currentPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;
}

bool Game::CheckPawnPromotion(Piece*** i_boardData)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (i_boardData[i][j] != nullptr && (i == 0 || i == BOARD_HEIGHT - 1) && i_boardData[i][j]->getName() == CellType::PAWN)
			{
				PawnPromotionCoordinate.x = i;
				PawnPromotionCoordinate.y = j;
				return true;
			}
		}
	}
	return false;
}

void Game::DrawGameOverScreen()
{
	m_renderer->DrawGameOverPopup();
	std::string game_result;
	switch (m_board->getGameResult())
	{
	case White_Player_WIN:
		game_result = "White Player WIN";
		break;
	case Black_Player_WIN:
		game_result = "Black Player WIN";
		break;
	default:
		break;
	}
	m_renderer->DrawText(game_result, TEXT_SIZE, TEXT_GAME_RESULT_X, TEXT_GAME_RESULT_Y, TEXT_GAME_RESULT_HEIGHT, TEXT_GAME_RESULT_WIDTH);
}

void Game::Update()
{
	while (!m_isPlayerWantExit)
	{	
		m_renderer->PreRendering();
		m_renderer->DrawTable();
		if (m_currentPiece != nullptr)
		{
			m_renderer->DrawAvailableMove(m_currentPieceCoordinate.x, m_currentPieceCoordinate.y, CurrentAvailableMove());
		}		
		DrawBoard();
		m_inputManager->UpdateInput();
		m_isPlayerWantExit = m_inputManager->IsGoingToQuit();
		GameResult gameResult = m_board->getGameResult();
		if (gameResult == GameResult::RUNNING)
		{
			Piece*** boardData = m_board->getBoardData();
			if (!CheckPawnPromotion(boardData))
			{
				if (m_inputManager->IsMouseUp())
				{
					int mouseX = m_inputManager->GetMouseX();
					int mouseY = m_inputManager->GetMouseY();
					if (boardData[(mouseY - SIZE_EDGE) / SIZE_CELL_PIXEL][(mouseX - SIZE_EDGE) / SIZE_CELL_PIXEL] != nullptr && boardData[(mouseY - SIZE_EDGE) / SIZE_CELL_PIXEL][(mouseX - SIZE_EDGE) / SIZE_CELL_PIXEL]->getColor() == m_currentPlayer)
					{
						setCurrentPiece((mouseY - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouseX - SIZE_EDGE) / SIZE_CELL_PIXEL);						
					}
					else if (m_currentPiece != nullptr && CheckValidMove((mouseY - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouseX - SIZE_EDGE) / SIZE_CELL_PIXEL))
					{
						UpdateMove((mouseY - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouseX - SIZE_EDGE) / SIZE_CELL_PIXEL);
					}
				}
			}
			else {				
				m_renderer->DrawPromotionPawn(PawnPromotionCoordinate.x, PawnPromotionCoordinate.y);
									
				if (m_inputManager->IsMouseUp())
				{
					int mouseX = m_inputManager->GetMouseX();
					int mouseY = m_inputManager->GetMouseY();
					m_board->PromotionPawn(PawnPromotionCoordinate.x, PawnPromotionCoordinate.y, (mouseY - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouseX - SIZE_EDGE) / SIZE_CELL_PIXEL);				
				}
			}
		}
		else {
			DrawGameOverScreen();

			if (m_inputManager->IsMouseUp())
			{
				int mouseX = m_inputManager->GetMouseX();
				int mouseY = m_inputManager->GetMouseY();

				if (mouseX >= YES_BUTTONL_X && mouseX <= YES_BUTTONL_X + YES_BUTTON_WIDTH && mouseY >= YES_BUTTON_Y && mouseY <= YES_BUTTON_Y + YES_BUTTON_HEIGHT)
				{
					CreateNewGame();
				}
				else if (mouseX >= NO_BUTTON_X && mouseX <= NO_BUTTON_X + NO_BUTTON_WIDTH && mouseY >= NO_BUTTON_Y && mouseY <= NO_BUTTON_Y + NO_BUTTON_HEIGHT) {
					m_isPlayerWantExit = true;
				}
			}

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

