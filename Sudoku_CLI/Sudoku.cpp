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

bool Sudoku::is_filled()
{
	return std::find(this->state.begin(), this->state.end(), 0) == this->state.end();
}

int Sudoku::increment(const COORD& coord, const int value, const bool cls)
{
	int new_value = this->state[coord.Y * 9 + coord.X] + value;
	if (new_value > 9) new_value = new_value - 9;

	this->fill_number(coord, new_value, cls);

	return new_value;
}

int Sudoku::get_state(const Sudoku& sudoku, const COORD& cursor)
{
	return sudoku.state[cursor.Y * 9 + cursor.X];
}

bool Sudoku::get_initial(const Sudoku& sudoku, const COORD& cursor)
{
	return sudoku.initial[cursor.Y * 9 + cursor.X];
}

void Sudoku::fill_number(const COORD& cursor, const int number, const bool update)
{
	int index = cursor.Y * 9 + cursor.X;

	if (this->initial[index]) return;

	this->state[index] = this->state[index] == number ? 0 : number;

	if (update)
		Utils::print_sudoku(*this);
}

void Sudoku::test_if_solved()
{
	if (std::find(this->state.begin(), this->state.end(), 0) != this->state.end()) return;

	this->solved = true;

	for (short y = 0; y < 9; y++)
		for (short x1 = 0; x1 < 8; x1++)
			for (short x2 = x1 + 1; x2 < 9; x2++)
				if (this->state[y * 9 + x1] == this->state[y * 9 + x2])
					this->solved = false;

	for (short x = 0; x < 9; x++)
		for (short y1 = 0; y1 < 8; y1++)
			for (short y2 = y1 + 1; y2 < 9; y2++)
				if (this->state[y1 * 9 + x] == this->state[y2 * 9 + x])
					this->solved = false;
	
	short s3 = 3;

	for (short y = 0; y < 3; y++)
		for (short x = 0; x < 3; x++)
			for (short oY1 = 0; oY1 < 3; oY1++)
				for (short oX1 = 0; oX1 < 3; oX1++)
					for (short oY2 = 0; oY2 < 3; oY2++)
						for (short oX2 = 0; oX2 < 3; oX2++)
							if ((oX1 == oX2 && oY1 == oY2) == false)
								if (this->state[(y * 3 + oY1) * 9 + x * 3 + oX1] == this->state[(y * 3 + oY2) * 9 + x * 3 + oX2])
									this->solved = false;
}