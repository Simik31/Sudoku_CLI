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

#include "BruteForce.h"
#include "BetterBruteForce.h"
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

	void solve_player();
	void solve_brute_force();

	int mm_choice;
	bool loaded = false;
	Sudoku sudoku;
	COORD cursor{ 0, 0 };
};

#endif


