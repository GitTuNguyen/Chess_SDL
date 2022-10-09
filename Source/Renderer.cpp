#include "Renderer.h"
#include <Windows.h>
#undef DrawText

Renderer::Renderer()
{
	//Hide console window
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);

	//Init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("Chess - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
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

	//Render in center of window
	SDL_RenderSetLogicalSize(m_sdlRenderer, WINDOW_WIDTH, WINDOW_HEIGHT);

	LoadTexture("Chess_Stone");

	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return;
	}
}

void Renderer::CleanUp()
{
	SDL_DestroyRenderer(m_sdlRenderer);	//cleans up all initialized subsystems

	SDL_DestroyWindow(m_window);	//Destroy a renderer
	
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
	std::string str = "Data/" + i_ImageName + ".png";
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

void Renderer::DrawCell(CellType i_cellType, Color i_color, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.w = SIZE_CELL_PIXEL;
	newRect.h = SIZE_CELL_PIXEL;
	newRect.x = i_pixelX + SIZE_EDGE;
	newRect.y = i_pixelY + SIZE_EDGE;

	if (i_cellType == CellType::KING)
	{
		if ( i_color == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KingB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KingW"], NULL, &newRect);
		}
	} 
	else if (i_cellType == CellType::QUEEN)
	{
		if (i_color == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["QueenB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["QueenW"], NULL, &newRect);
		}

		}
	else if (i_cellType == CellType::BISHOP)
	{
		if (i_color == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["BishopB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["BishopW"], NULL, &newRect);
		}
	}
	else if (i_cellType == CellType::KNIGHT)
	{
		if (i_color == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KnightB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["KnightW"], NULL, &newRect);
		}
	}
	else if (i_cellType == CellType::CASTLE)
	{
		if (i_color == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["CastleB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["CastleW"], NULL, &newRect);
		}
	}
	else if (i_cellType == CellType::PAWN)
	{
		if (i_color == Color::BLACK)
		{
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["PawnB"], NULL, &newRect);
		}
		else {
			SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["PawnW"], NULL, &newRect);
		}
	}
}

void Renderer::DrawSelectionPromotionPawn(int i_DrawX, int i_DrawY, Color i_color)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			DrawCell(CellType::QUEEN, i_color, i_DrawX - SIZE_EDGE, i_DrawY - SIZE_EDGE);			
		}
		else if (i == 1)
		{
			DrawCell(CellType::KNIGHT, i_color, i_DrawX - SIZE_EDGE, i_DrawY - SIZE_EDGE + SIZE_CELL_PIXEL);
		}
		else if (i == 2)
		{
			DrawCell(CellType::CASTLE, i_color, i_DrawX - SIZE_EDGE, i_DrawY - SIZE_EDGE + (2 * SIZE_CELL_PIXEL) );
		}
		else if (i == 3)
		{
			DrawCell(CellType::BISHOP, i_color, i_DrawX - SIZE_EDGE, i_DrawY - SIZE_EDGE + (3 * SIZE_CELL_PIXEL));
		}
	}
}

void Renderer::DrawPromotionPawn(int i_PawnX, int i_PawnY)
{
	Color tempColor;
	SDL_Rect newRect;
	newRect.h = SIZE_CELL_PIXEL * 4;
	newRect.w = SIZE_CELL_PIXEL;
	if (i_PawnX == 0)
	{
		newRect.y = SIZE_EDGE;
		tempColor = Color::WHITE;
	}
	else {
		newRect.y = (BOARD_HEIGHT - 4) * SIZE_CELL_PIXEL + SIZE_EDGE;
		tempColor = Color::BLACK;
	}
	if (i_PawnY == 0)
	{
		newRect.x = (i_PawnY + 1) * SIZE_CELL_PIXEL + SIZE_EDGE;
	}
	else {
		newRect.x = (i_PawnY - 1) * SIZE_CELL_PIXEL + SIZE_EDGE;
	}

	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(m_sdlRenderer, &newRect);

	DrawSelectionPromotionPawn(newRect.x, newRect.y, tempColor);
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

void Renderer::DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W)
{
	TTF_Font* font = TTF_OpenFont("Data/font.ttf", i_size);
	SDL_Color White = { 255, 255, 255 };
	const char* renderText = i_text.c_str();
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, renderText, White);
	SDL_Texture* message = SDL_CreateTextureFromSurface(m_sdlRenderer, surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = i_X;
	Message_rect.y = i_Y;
	Message_rect.w = i_W;
	Message_rect.h = i_H;
	SDL_RenderCopy(m_sdlRenderer, message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Renderer::DrawGameOverPopup()
{
	SDL_Rect newRect;
	newRect.w = GAME_OVER_POPUP_WIDTH;
	newRect.h = GAME_OVER_POPUP_HEIGHT;
	newRect.x = GAME_OVER_POPUP_X;
	newRect.y = GAME_OVER_POPUP_Y;

	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(m_sdlRenderer, &newRect);

	DrawText("GAME OVER", TEXT_SIZE, TEXT_GAME_OVER_X, TEXT_GAME_OVER_Y, TEXT_GAME_OVER_HEIGHT, TEXT_GAME_OVER_WIDTH);

	DrawText("PLAY AGAIN?", TEXT_SIZE, TEXT_PLAY_AGAIN_X, TEXT_PLAY_AGAIN_Y, TEXT_PLAY_AGAIN_HEIGHT, TEXT_PLAY_AGAIN_WIDTH);

	newRect.w = YES_BUTTON_WIDTH;
	newRect.h = YES_BUTTON_HEIGHT;
	newRect.x = YES_BUTTONL_X;
	newRect.y = YES_BUTTON_Y;
	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["YES"], NULL, &newRect);

	newRect.w = NO_BUTTON_WIDTH;
	newRect.h = NO_BUTTON_HEIGHT;
	newRect.x = NO_BUTTON_X;
	newRect.y = NO_BUTTON_Y;
	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["NO"], NULL, &newRect);
}