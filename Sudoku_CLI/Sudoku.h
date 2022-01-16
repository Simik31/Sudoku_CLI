#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <Windows.h>

class Sudoku
{
public:
	Sudoku();
	Sudoku(const std::vector<int>& initial_state);

	bool is_solved();
	bool is_filled();
	int increment(const COORD& coord, const int value = 1, const bool cls = true);
	static int get_state(const Sudoku& sudoku, const COORD& cursor);
	static bool get_initial(const Sudoku& sudoku, const COORD& cursor);

	void fill_number(const COORD& cursor, const int number, const bool update = true);
	void test_if_solved();

private:
	bool solved = false;

	std::vector<int> state;
	std::vector<bool> initial;
};

#endif