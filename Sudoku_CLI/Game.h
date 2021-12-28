#pragma once
#ifndef GAME_H
#define GAME_H

#define KEY_ENTER 13
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

#include <vector>
#include <iostream>
#include <conio.h>
#include <string>

#include "Sudoku.h"
#include "Utils.h"

class Game
{
public:
	void main_menu();
	void run();

private:
	void load_by_hand();
	void load_from_file();
	void load_default();

	bool loaded = false;
	Sudoku sudoku;
	int cursor_x = 0, cursor_y = 0;
};

#endif


