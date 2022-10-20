#pragma once
#include "Board.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <map>
#include <string>

class Renderer {
public:
	Renderer();
	void DrawPiece(PieceType i_cellType, Color i_color, int i_pixelX, int i_pixelY);
	void DrawBoadData();
	void DrawTable();
	void DrawSelectionPromotionPawn(int i_DrawX, int i_DrawY, Color i_color);
	void DrawPromotionPawn(Coordinate i_pawnPromotionCoordiante);
	void DrawAvailableMove(Coordinate i_selectedPieceCoordinate, std::vector<Coordinate> i_availableMove);
	void DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W);
	void DrawGameOverPopup();
	void PostFrame();
	void CleanUp();
	void LoadTexture(std::string i_imageName);
	void LoadPieceTexture(std::string i_imageName, PieceType i_type, Color i_color);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	std::map<std::string, SDL_Texture*> m_loadedTextures;
	std::map<std::pair<PieceType, Color>, SDL_Texture*> m_loadedPieceTextures;
};