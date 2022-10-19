#pragma once
#define SDL_MAIN_HANDLED

//Board
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

#define CELL_SIZE 80
#define LEFT_EDGE 20
#define TOP_EDGE 22
#define BOTTOM_EDGE 20
#define RIGHT_EDGE 20

//Window

#define WINDOW_HEIGHT 680
#define WINDOW_WIDTH 680
#define AMOUNT_OF_FILE_PICTURE 17

//Gameover popup
#define GAME_OVER_POPUP_WIDTH 480
#define GAME_OVER_POPUP_HEIGHT 322
#define GAME_OVER_POPUP_X ((WINDOW_WIDTH - GAME_OVER_POPUP_WIDTH) / 2)
#define GAME_OVER_POPUP_Y (((WINDOW_HEIGHT - GAME_OVER_POPUP_HEIGHT) / 2) + 1)

//Text
#define TEXT_SIZE 32

#define TEXT_GAME_OVER_WIDTH 320
#define TEXT_GAME_OVER_HEIGHT 70
#define TEXT_GAME_OVER_X (GAME_OVER_POPUP_X + (GAME_OVER_POPUP_WIDTH - TEXT_GAME_OVER_WIDTH) / 2)
#define TEXT_GAME_OVER_Y (GAME_OVER_POPUP_Y + 5)


#define TEXT_GAME_RESULT_WIDTH 320
#define TEXT_GAME_RESULT_HEIGHT 70
#define TEXT_GAME_RESULT_X (GAME_OVER_POPUP_X + (GAME_OVER_POPUP_WIDTH - TEXT_GAME_RESULT_WIDTH) / 2)
#define TEXT_GAME_RESULT_Y (GAME_OVER_POPUP_Y + CELL_SIZE + 5)

#define TEXT_PLAY_AGAIN_WIDTH 160
#define TEXT_PLAY_AGAIN_HEIGHT 70
#define TEXT_PLAY_AGAIN_X (GAME_OVER_POPUP_X + (GAME_OVER_POPUP_WIDTH - TEXT_PLAY_AGAIN_WIDTH) / 2)
#define TEXT_PLAY_AGAIN_Y (GAME_OVER_POPUP_Y + CELL_SIZE * 2 + 5)

//Button
#define YES_BUTTON_WIDTH (CELL_SIZE - 10)
#define YES_BUTTON_HEIGHT (CELL_SIZE - 10)
#define YES_BUTTONL_X (GAME_OVER_POPUP_X + CELL_SIZE + 5)
#define YES_BUTTON_Y (GAME_OVER_POPUP_Y + CELL_SIZE * 3 + 5)

#define NO_BUTTON_WIDTH (CELL_SIZE - 10)
#define NO_BUTTON_HEIGHT (CELL_SIZE - 10)
#define NO_BUTTON_X (YES_BUTTONL_X + CELL_SIZE * 3)
#define NO_BUTTON_Y YES_BUTTON_Y

enum PieceType {
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
	int row;
	int col;

	Coordinate() {}

	Coordinate(int i_row, int i_col)
	{
		row = i_row;
		col = i_col;
	}
};
