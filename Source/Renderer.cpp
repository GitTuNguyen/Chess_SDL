#include "Renderer.h"
#ifndef __ANDROID__
#include <Windows.h>
#endif
#undef DrawText

Renderer::Renderer()
{
	//Hide console window
#ifndef __ANDROID__
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
#endif

	//Init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("Chess - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

	IMG_Init(IMG_INIT_PNG);
}

void Renderer::CleanUp()
{
	for (auto iter : m_loadedTextures)
	{
		SDL_DestroyTexture(iter.second);
	}

	for (auto iter : m_loadedPieceTextures)
	{
		SDL_DestroyTexture(iter.second);
	}

	for (auto iter : m_loadedFonts)
	{
		TTF_CloseFont(iter.second);
	}

	SDL_DestroyRenderer(m_sdlRenderer);	//cleans up all initialized subsystems

	SDL_DestroyWindow(m_window);	//Destroy window
	
	SDL_Quit();
}

void Renderer::PostFrame()
{
	SDL_RenderPresent(m_sdlRenderer);
	SDL_Delay(16);
}

void Renderer::LoadTexture(std::string i_ImageName)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	std::string str = "Data/" + i_ImageName + ".png";
	tempSurface = IMG_Load(str.c_str());
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedTextures.insert(std::pair<std::string, SDL_Texture*>(i_ImageName, texture));
}

void Renderer::LoadPieceTexture(std::string i_imageName, PieceType i_type, Color i_color)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	std::string str = "Data/" + i_imageName + ".png";
	tempSurface = IMG_Load(str.c_str());
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedPieceTextures.insert(std::make_pair(std::make_pair(i_type, i_color), texture));
}

void Renderer::DrawTable()
{
	SDL_Rect newRect;
	newRect.w = WINDOW_WIDTH;
	newRect.h = WINDOW_HEIGHT;
	newRect.x = 0;
	newRect.y = 0;
	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["Chess_Stone"], NULL, &newRect);
}

void Renderer::PreRendering()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_sdlRenderer);
}

void Renderer::DrawPiece(PieceType i_cellType, Color i_color, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.w = CELL_SIZE;
	newRect.h = CELL_SIZE;
	newRect.x = i_pixelX + LEFT_EDGE;
	newRect.y = i_pixelY + TOP_EDGE;

	SDL_RenderCopy(m_sdlRenderer, m_loadedPieceTextures[std::make_pair(i_cellType, i_color)], NULL, &newRect);
}

void Renderer::DrawSelectionPromotionPawn(int i_DrawX, int i_DrawY, Color i_color)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			DrawPiece(PieceType::QUEEN, i_color, i_DrawX - LEFT_EDGE, i_DrawY - LEFT_EDGE);			
		}
		else if (i == 1)
		{
			DrawPiece(PieceType::KNIGHT, i_color, i_DrawX - LEFT_EDGE, i_DrawY - LEFT_EDGE + CELL_SIZE);
		}
		else if (i == 2)
		{
			DrawPiece(PieceType::CASTLE, i_color, i_DrawX - LEFT_EDGE, i_DrawY - LEFT_EDGE + (2 * CELL_SIZE) );
		}
		else if (i == 3)
		{
			DrawPiece(PieceType::BISHOP, i_color, i_DrawX - LEFT_EDGE, i_DrawY - LEFT_EDGE + (3 * CELL_SIZE));
		}
	}
}

void Renderer::DrawPromotionPawn(Coordinate i_pawnPromotionCoordiante)
{
	Color tempColor;
	SDL_Rect newRect;
	newRect.h = CELL_SIZE * 4;
	newRect.w = CELL_SIZE;
	if (i_pawnPromotionCoordiante.row == 0)
	{
		newRect.y = TOP_EDGE;
		tempColor = Color::WHITE;
	}
	else {
		newRect.y = (BOARD_HEIGHT - 4) * CELL_SIZE + TOP_EDGE;
		tempColor = Color::BLACK;
	}
	if (i_pawnPromotionCoordiante.col == 0)
	{
		newRect.x = (i_pawnPromotionCoordiante.col + 1) * CELL_SIZE + LEFT_EDGE;
	}
	else {
		newRect.x = (i_pawnPromotionCoordiante.col - 1) * CELL_SIZE + LEFT_EDGE;
	}

	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(m_sdlRenderer, &newRect);

	DrawSelectionPromotionPawn(newRect.x, newRect.y, tempColor);
}

void Renderer::DrawAvailableMove(Coordinate i_selectedPieceCoordinate, std::vector<Coordinate> i_availableMove)
{
	SDL_Rect newRect;
	newRect.x = i_selectedPieceCoordinate.col * CELL_SIZE + LEFT_EDGE;
	newRect.y = i_selectedPieceCoordinate.row * CELL_SIZE + TOP_EDGE;
	newRect.h = CELL_SIZE;
	newRect.w = CELL_SIZE;
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 128, 0, 150);
	SDL_RenderFillRect(m_sdlRenderer, &newRect);
	SDL_SetRenderDrawColor(m_sdlRenderer, 31, 224, 108, 150);
	for (int i = 0; i < i_availableMove.size(); i++)
	{
		newRect.x = i_availableMove[i].col * CELL_SIZE + LEFT_EDGE;
		newRect.y = i_availableMove[i].row * CELL_SIZE + TOP_EDGE;
		SDL_RenderFillRect(m_sdlRenderer, &newRect);
	}
}

void Renderer::DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W)
{
	TTF_Font* font;
	if (m_loadedFonts.find(i_size) == m_loadedFonts.end())
	{
		font = TTF_OpenFont("Data/font.ttf", i_size);
		m_loadedFonts.insert({ i_size, font });
	}
	else
	{
		font = m_loadedFonts[i_size];
	}
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