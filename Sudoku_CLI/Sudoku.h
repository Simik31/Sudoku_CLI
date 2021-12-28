#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

class Sudoku
{
public:
	Sudoku();
	Sudoku(const std::vector<int>& initial_state);

	bool is_solved();
	static int get_state(const Sudoku& sudoku, const int index);
	static bool get_initial(const Sudoku& sudoku, const int index);

	void fill_number(const int cell_x, const int cell_y, const int number);
	void test_if_solved();

private:
	bool solved = false;

	std::vector<int> state;
	std::vector<bool> initial;
};

#endif