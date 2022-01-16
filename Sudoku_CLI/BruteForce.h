#pragma once

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <algorithm>
#include <chrono>
#include <thread>
#include <Windows.h>

#include "Game.h"
#include "Sudoku.h"

class BruteForce
{
public:
	BruteForce(const Sudoku& _sudoku) : sudoku{ _sudoku } {};
	void solve();

private:
	void step(int coord_index);
	void update_ui();

	std::vector<COORD> coords;
	Sudoku sudoku;
	std::chrono::high_resolution_clock::time_point solution_start, loop_start, loop_end;
	double iter = 0, max_iter = 1;
	std::thread ui_thread;
};

#endif