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
	std::string file_name[AMOUNT_OF_FILE_PICTURE] = { "KingB", "KingW", "QueenB", "QueenW", "BishopB", "BishopW", "KnightB", "KnightW", "CastleB", "CastleW", "PawnB", "PawnW", "CasaVerde", "CasaVerde_", "B_win", "W_win", "Chess_Stone"};
	for (int i = 0; i < sizeof(file_name) / sizeof(std::string); i++)
	{
		m_renderer->LoadTexture(file_name[i]);
	}
}

void Game::Rematch()
{
	char inputPlayer;
	std::cout << "Play again? (Y to play again, another key to quit): ";
	std::cin >> inputPlayer;
	if (inputPlayer == 'Y' || inputPlayer == 'y')
	{
		CreateNewGame();
	}
	else {
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
				m_renderer->DrawCell(boardData[i][j], j * SIZE_CELL_PIXEL, i * SIZE_CELL_PIXEL);
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
				case SDL_MOUSEBUTTONDOWN:
				{
					Piece*** boardData = m_board->getBoardData();
					int mouse_X = mainEvent.motion.x;
					int mouse_Y = mainEvent.motion.y;
					if (boardData[(mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL][(mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL] != nullptr && boardData[(mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL][(mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL]->getColor() == m_currentPlayer)
					{
						setCurrentPiece((mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL);
						m_renderer->PreRendering();
						m_renderer->DrawAvailableMove(m_currentPieceCoordinate.x, m_currentPieceCoordinate.y, CurrentAvailableMove());
						DrawBoard();
					}
					else if (m_currentPiece != nullptr &&  CheckValidMove((mouse_Y - SIZE_EDGE) / SIZE_CELL_PIXEL, (mouse_X - SIZE_EDGE) / SIZE_CELL_PIXEL))
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
		}
		else {
			Rematch();
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