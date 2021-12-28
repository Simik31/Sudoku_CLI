#include "Sudoku.h"
#include "Utils.h"

Sudoku::Sudoku()
{
	this->state.reserve(81);
	this->initial.reserve(81);

	for (int i = 0; i < 81; i++)
	{
		this->state.push_back(0);
		this->initial.push_back(false);
	}
}

Sudoku::Sudoku(const std::vector<int>& initial_state)
{
	this->state = initial_state;
	for (int state : initial_state) this->initial.push_back(state > 0);
}

bool Sudoku::is_solved()
{
	return this->solved;
}

int Sudoku::get_state(const Sudoku& sudoku, const int index)
{
	return sudoku.state[index];
}

bool Sudoku::get_initial(const Sudoku& sudoku, const int index)
{
	return sudoku.initial[index];
}

void Sudoku::fill_number(const int cell_x, const int cell_y, const int number)
{
	int index = cell_y * 9 + cell_x;

	if (this->initial[index]) return;

	this->state[index] = this->state[index] == number ? 0 : number;

	Utils::print_sudoku(*this);
}

void Sudoku::test_if_solved()
{
	if (std::find(this->state.begin(), this->state.end(), 0) != this->state.end()) return;

	this->solved = true;

	for (int y = 0; y < 9; y++)
		for (int x1 = 0; x1 < 8; x1++)
			for (int x2 = x1 + 1; x2 < 9; x2++)
				if (this->state[y * 9 + x1] == this->state[y * 9 + x2])
				{
					Utils::highlight_cell(*this, x1, y);
					Utils::highlight_cell(*this, x2, y);
					this->solved = false;
				}

	for (int x = 0; x < 9; x++)
		for (int y1 = 0; y1 < 8; y1++)
			for (int y2 = y1 + 1; y2 < 9; y2++)
				if (this->state[y1 * 9 + x] == this->state[y2 * 9 + x])
				{
					Utils::highlight_cell(*this, x, y1);
					Utils::highlight_cell(*this, x, y2);
					this->solved = false;
				}
	
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
			for (int oY1 = 0; oY1 < 3; oY1++)
				for (int oX1 = 0; oX1 < 3; oX1++)
					for (int oY2 = 0; oY2 < 3; oY2++)
						for (int oX2 = 0; oX2 < 3; oX2++)
							if ((oX1 == oX2 && oY1 == oY2) == false)
								if (this->state[(y * 3 + oY1) * 9 + x * 3 + oX1] == this->state[(y * 3 + oY2) * 9 + x * 3 + oX2])
								{
									Utils::highlight_cell(*this, x * 3 + oX1, y * 3 + oY1);
									Utils::highlight_cell(*this, x * 3 + oX2, y * 3 + oY2);
									this->solved = false;
								}
}