#pragma once
#include "Board.h"
#include "SDL.h"
#include "SDL_image.h"
#include "ConstValue.h"
#include <map>
#include <string>
class Renderer {
public:
	Renderer();
	void DrawCell(Piece* i_cell, int i_pixelX, int i_pixelY);
	void DrawBoadData();
	void DrawTable();
	void DrawAvailableMove(int i_CurrentPiece_X, int i_CurrentPiece_Y, std::vector<Coordinate> i_availableMove);
	void PostFrame();
	void CleanUp();
	void LoadTexture(std::string i_imageName);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	std::map<std::string, SDL_Texture*> m_loadedTextures;
};