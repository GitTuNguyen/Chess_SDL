#pragma once
#include "Board.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "ConstValue.h"
#include <map>
#include <string>

class Renderer {
public:
	Renderer();
	void DrawCell(CellType i_cellType, Color i_color, int i_pixelX, int i_pixelY);
	void DrawBoadData();
	void DrawTable();
	void DrawSelectionPromotionPawn(int i_DrawX, int i_DrawY, Color i_color);
	void DrawPromotionPawn(int i_PawnX, int i_PawnY);
	void DrawAvailableMove(int i_CurrentPiece_X, int i_CurrentPiece_Y, std::vector<Coordinate> i_availableMove);
	void DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W);
	void DrawGameOverPopup();
	void PostFrame();
	void CleanUp();
	void LoadTexture(std::string i_imageName);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	std::map<std::string, SDL_Texture*> m_loadedTextures;
};