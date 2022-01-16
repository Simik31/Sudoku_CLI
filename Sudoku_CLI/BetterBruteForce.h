#ifndef BETTER_BRUTEFORCE_H
#define BETTER_BRUTEFORCE_H

#include <algorithm>
#include <chrono>
#include <thread>
#include <Windows.h>

#include "Game.h"
#include "Sudoku.h"

class BetterBruteForce
{
public:
	BetterBruteForce(const Sudoku& _sudoku) : sudoku{ _sudoku } {};
	void solve();

private:
	void step(int coord_index);
	bool is_valid(const COORD& cursor);

	std::vector<COORD> coords;
	Sudoku sudoku;
};

#endif