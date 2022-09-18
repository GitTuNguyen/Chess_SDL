#include "Game.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_currentPlayer = Color::WHITE;
	m_isPlayerWantExit = false;
	m_currentPiece = nullptr;
	LoadPicture();
}

void Game::CreateNewGame()
{
	m_board->Reset();
	m_renderer->PreRendering();
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

void Game::Rematch(int i_mouse_X, int i_mouse_Y)
{

	if (i_mouse_X >= YES_CELL_X && i_mouse_X <= YES_CELL_X + YES_CELL_WIDTH && i_mouse_Y >= YES_CELL_Y && i_mouse_Y <= YES_CELL_Y + YES_CELL_HEIGHT)
	{
		CreateNewGame();
	}
	else if (i_mouse_X >= NO_CELL_X && i_mouse_X <= NO_CELL_X + NO_CELL_WIDTH && i_mouse_Y >= NO_CELL_Y && i_mouse_Y <= NO_CELL_Y + NO_CELL_HEIGHT) {
		m_isPlayerWantExit = true;
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
	m_renderer->DrawText(game_result, TEXT_GAME_RESULT_SIZE, TEXT_GAME_RESULT_X, TEXT_GAME_RESULT_Y, TEXT_GAME_RESULT_HEIGHT, TEXT_GAME_RESULT_WIDTH);
}

void Game::Update()
{
	m_renderer->PreRendering();
	DrawBoard();
	while (!m_isPlayerWantExit)
	{
		GameResult gameResult = m_board->getGameResult();
		if (gameResult == GameResult::RUNNING)
		{
			while (SDL_PollEvent(&mainEvent))
			{
				switch (mainEvent.type)
				{
				case SDL_QUIT:
				{
					m_isPlayerWantExit = true;
					break;
				}
				default:
				{
					break;
				}
				}
				Piece*** boardData = m_board->getBoardData();
				if (!CheckPawnPromotion(boardData))
				{
					switch (mainEvent.type)
					{
					case SDL_MOUSEBUTTONDOWN:
					{
						int mouse_X = mainEvent.motion.x;
						int mouse_Y = mainEvent.motion.y;
						if (boardData[(mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL][(mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL] != nullptr && boardData[(mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL][(mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL]->getColor() == m_currentPlayer)
						{
							setCurrentPiece((mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL);
							m_renderer->PreRendering();
							m_renderer->DrawAvailableMove(m_currentPieceCoordinate.x, m_currentPieceCoordinate.y, CurrentAvailableMove());
							DrawBoard();
						}
						else if (m_currentPiece != nullptr && CheckValidMove((mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL))
						{
							UpdateMove((mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL);
							m_renderer->PreRendering();
							DrawBoard();
						}
					}
					default:
					{
						break;
					}
					}
					
				}
				else {
					m_renderer->PreRendering();
					DrawBoard();
					m_renderer->DrawPromotionPawn(PawnPromotionCoordinate.x, PawnPromotionCoordinate.y);
					switch (mainEvent.type)
					{
					case SDL_MOUSEBUTTONDOWN:
					{
						int mouse_X = mainEvent.motion.x;
						int mouse_Y = mainEvent.motion.y;
						m_board->PromotionPawn(PawnPromotionCoordinate.x, PawnPromotionCoordinate.y, (mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL);
						m_renderer->PreRendering();
						DrawBoard();
					}
					default:
					{
						break;
					}
					}
				}
			}
		}
		else {
			DrawGameOverScreen();
			SDL_Rect newRect;
			while (SDL_PollEvent(&mainEvent))
			{
				switch (mainEvent.type)
				{
				case SDL_QUIT:
				{
					m_isPlayerWantExit = true;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					newRect.x = mainEvent.motion.x;
					newRect.y = mainEvent.motion.y;
					Rematch(newRect.x, newRect.y);
				}
				default:
				{
					break;
				}
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
}