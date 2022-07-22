#include "Renderer.h"

Renderer::Renderer()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("Tic And Toe - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return;
	}


	//create a renderer
	m_sdlRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(m_sdlRenderer,SDL_BlendMode::SDL_BLENDMODE_BLEND);
	if (m_sdlRenderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return;
	}
	LoadTexture("Chess_Stone");
}

void Renderer::CleanUp()
{

	SDL_DestroyWindow(m_window);

	//Destroy a renderer
	SDL_DestroyRenderer(m_sdlRenderer);

	//cleans up all initialized subsystems
	SDL_Quit();
}

void Renderer::PostFrame()
{
	SDL_RenderPresent(m_sdlRenderer);
	SDL_Delay(16);
}

void Renderer::LoadTexture(std::string i_ImageName)
{
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	std::string str = "./Data/" + i_ImageName + ".png";
	tempSurface = IMG_Load(str.c_str());
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedTextures.insert(std::pair<std::string, SDL_Texture*>(i_ImageName, texture));
}
void Renderer::DrawTable()
{
	SDL_Rect newRect;
	newRect.w = WINDOW_WIDTH;
	newRect.h = WINDOW_HEIGHT;
	newRect.x = 0;
	newRect.y = 0;
	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["Chess_Stone"], NULL, &newRect);
	SDL_RenderPresent(m_sdlRenderer);
}

void Renderer::PreRendering()
{
	
	DrawTable();
}

void Renderer::DrawCell(Piece* i_cell, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.w = SIZE_CELL_PIXEL;
	newRect.h = SIZE_CELL_PIXEL;
	newRect.x = i_pixelX + SIZE_EDGE;
	newRect.y = i_pixelY + SIZE_EDGE;

	if (i_cell->getName() == CellType::KING)
	{
		if (i_cell->getColor() == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KingB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KingW"], NULL, &newRect);
		}
	} 
	else if (i_cell->getName() == CellType::QUEEN)
	{
		if (i_cell->getColor() == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["QueenB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["QueenW"], NULL, &newRect);
		}

		}
	else if (i_cell->getName() == CellType::BISHOP)
	{
		if (i_cell->getColor() == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["BishopB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["BishopW"], NULL, &newRect);
		}
	}
	else if (i_cell->getName() == CellType::KNIGHT)
	{
		if (i_cell->getColor() == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KnightB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KnightW"], NULL, &newRect);
		}
	}
	else if (i_cell->getName() == CellType::CASTLE)
	{
		if (i_cell->getColor() == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["CastleB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["CastleW"], NULL, &newRect);
		}
	}
	else if (i_cell->getName() == CellType::PAWN)
	{
		if (i_cell->getColor() == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["PawnB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["PawnW"], NULL, &newRect);
		}
	}
}

void Renderer::DrawAvailableMove(int i_CurrentPiece_X, int i_CurrentPiece_Y, std::vector<Coordinate> i_availableMove)
{
	SDL_Rect newRect;
	newRect.x = i_CurrentPiece_Y * SIZE_CELL_PIXEL + SIZE_EDGE;
	newRect.y = i_CurrentPiece_X * SIZE_CELL_PIXEL + SIZE_EDGE + 1;
	newRect.h = SIZE_CELL_PIXEL + 1;
	newRect.w = SIZE_CELL_PIXEL;
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 128, 0, 150);
	SDL_RenderFillRect(m_sdlRenderer, &newRect);
	SDL_SetRenderDrawColor(m_sdlRenderer, 31, 224, 108, 150);
	for (int i = 0; i < i_availableMove.size(); i++)
	{
		newRect.x = i_availableMove[i].y * SIZE_CELL_PIXEL + SIZE_EDGE;
		newRect.y = i_availableMove[i].x * SIZE_CELL_PIXEL + SIZE_EDGE;
		SDL_RenderFillRect(m_sdlRenderer, &newRect);
	}
}