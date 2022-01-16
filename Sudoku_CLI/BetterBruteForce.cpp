#include "BetterBruteForce.h"

void BetterBruteForce::solve()
{
	for (short y = 0; y < 9; y++)
		for (short x = 0; x < 9; x++)
		{
			COORD coord{ x, y };
			if (!Sudoku::get_initial(this->sudoku, coord)) this->coords.push_back(coord);
		}

	std::chrono::high_resolution_clock::time_point solution_start = std::chrono::high_resolution_clock::now();

	this->step(0);
	this->sudoku.test_if_solved();

	Utils::print_sudoku(this->sudoku);

	if (!this->sudoku.is_solved()) std::cout << "No solution found!" << std::endl;
	std::cout << "Total time: " << (std::chrono::high_resolution_clock::now() - solution_start).count() / 1000000000.0 << "s" << std::endl;
}

void BetterBruteForce::step(int coord_index)
{
	if (coord_index < 0 || coord_index >= this->coords.size()) return;

	if (Sudoku::get_state(this->sudoku, this->coords[coord_index]) < 9)
	{
		int now = this->sudoku.increment(this->coords[coord_index], 1, false);

		if (this->is_valid(this->coords[coord_index])) step(coord_index + 1);
		else
		{
			if (now < 9) step(coord_index);
			else
			{
				this->sudoku.fill_number(this->coords[coord_index], now, false);
				step(coord_index - 1);
			}
		}
	}
	else
	{
		if (coord_index == 0) return;

		this->sudoku.fill_number(this->coords[coord_index], 9, false);
		step(coord_index - 1);
	}
}

bool BetterBruteForce::is_valid(const COORD& cursor)
{
	for (short o1 = 0; o1 < 8; o1++)
		for (short o2 = o1 + 1; o2 < 9; o2++)
		{
			int v1 = Sudoku::get_state(this->sudoku, COORD{ o1, cursor.Y });
			int v2 = Sudoku::get_state(this->sudoku, COORD{ o2, cursor.Y });

			if (v1 == v2 && (v1 != 0)) return false;

			int v3 = Sudoku::get_state(this->sudoku, COORD{ cursor.X, o1 });
			int v4 = Sudoku::get_state(this->sudoku, COORD{ cursor.X, o2 });

			if (v3 == v4 && (v3 != 0)) return false;
		}

	short s3 = 3;
	short x = cursor.X / s3;
	short y = cursor.Y / s3;

	for (short oY1 = 0; oY1 < 3; oY1++)
		for (short oY2 = 0; oY2 < 3; oY2++)
			for (short oX1 = 0; oX1 < 3; oX1++)
				for (short oX2 = 0; oX2 < 3; oX2++)
					if (oX1 != oX2 || oY1 != oY2)
					{
						int v1 = Sudoku::get_state(sudoku, COORD{ x * s3 + oX1, y * s3 + oY1 });
						int v2 = Sudoku::get_state(sudoku, COORD{ x * s3 + oX2, y * s3 + oY2 });

						if (v1 == v2 && (v1 != 0)) return false;
					}
	return true;
}
