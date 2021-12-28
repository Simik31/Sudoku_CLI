#pragma once
#ifndef UTILS_H
#define UTILS_H

#define SET_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)
#define WRAP(num) (((num) % 9 + 9) % 9)
#define MOVE_CURSOR_TO_CELL(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ short(x * 2 + 1), short(y * 2 + 1) })

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

#include "Sudoku.h"

class Utils
{
public:
	static void print_sudoku(const Sudoku& sudoku);
	static void highlight_cell(Sudoku& sudoku, const int x, const int y);
	static std::vector<std::string> read_lines_from_file(const std::string& filename);
};

#endif