#pragma once
#ifndef UTILS_H
#define UTILS_H

#define SET_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)
#define WRAP(num) (((num) % 9 + 9) % 9)

#include <iostream>
#include <iomanip>
#include <locale>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <filesystem>

#include "Sudoku.h"

class Utils
{
public:
	static void print_sudoku(const Sudoku& sudoku, const bool cls = true);
	static void highlight_cell(Sudoku& sudoku, const COORD& cursor);
	static void read_lines_from_file(const std::string& filename, std::vector<std::string>& lines);
	static void move_cursor(const COORD& cursor);
	static std::string ms_to_timestamp(const double& millis);
	static void highlight_mistakes(Sudoku& sudoku);
	static std::string format_comas(const double& value, const int precision);
};

#endif