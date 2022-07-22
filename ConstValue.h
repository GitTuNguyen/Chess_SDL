#pragma once
#define SDL_MAIN_HANDLED
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define SIZE_CELL_PIXEL 80
#define SIZE_EDGE 20
#define BOARD_X SIZE_EDGE
#define BOARD_Y SIZE_EDGE
#define WINDOW_HEIGHT 680
#define WINDOW_WIDTH 680
#define AMOUNT_OF_FILE_PICTURE 17

enum CellType {
	KING, //Vua
	QUEEN, //Hau
	BISHOP, //Tuong
	CASTLE, //Xe
	KNIGHT, //Ma
	PAWN,	//Tot
	NONE
};

enum Color {
	WHITE = 1,
	BLACK = -1
};

struct Coordinate {
	int x;
	int y;
};
