#include "BruteForce.h"

void BruteForce::solve()
{
	Utils::print_sudoku(this->sudoku);

	for (short y = 0; y < 9; y++)
		for (short x = 0; x < 9; x++)
		{
			COORD coord{ x, y };

			if (!Sudoku::get_initial(this->sudoku, coord))
			{
				this->coords.push_back(coord);
				this->sudoku.fill_number(coord, 1, false);
			}
		}

	std::reverse(this->coords.begin(), this->coords.end());

	this->max_iter = std::pow(9, this->coords.size());
	this->ui_thread = std::thread{ &BruteForce::update_ui, this };
	this->solution_start = std::chrono::high_resolution_clock::now();

	while (!this->sudoku.is_solved())
	{
		this->loop_start = std::chrono::high_resolution_clock::now();

		this->step(0);
		this->sudoku.test_if_solved();

		this->loop_end = std::chrono::high_resolution_clock::now();

		if (WaitForSingleObject(this->ui_thread.native_handle(), 0) == WAIT_OBJECT_0)
		{
			this->ui_thread.join();
			this->ui_thread = std::thread{ &BruteForce::update_ui, this };
		}

		if (this->iter >= this->max_iter) // ALl solutions tested, no solution found
			break;
	}

	this->ui_thread.join();

	Utils::print_sudoku(this->sudoku);

	if (!this->sudoku.is_solved())
		std::cout << "No solution found!" << std::endl;

	double time = (std::chrono::high_resolution_clock::now() - this->solution_start).count() / 1000000000.0;
	printf("Total time: %27.8f secs %s", time, Utils::ms_to_timestamp(time).c_str());
}

void BruteForce::step(int coord_index)
{
	if (coord_index >= this->coords.size()) return;
	this->iter++;
	if (this->sudoku.increment(this->coords[coord_index], 1, false) == 1) step(coord_index + 1);
}

void BruteForce::update_ui()
{
	while (!this->sudoku.is_solved())
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
		Utils::print_sudoku(this->sudoku, false);

		double loop_secs =     std::abs((this->loop_end - this->loop_start).count() / 1000000000.0);
		double solution_secs = std::abs((this->loop_end - this->solution_start).count() / 1000000000.0);
		double predict_secs =  solution_secs / this->iter * this->max_iter;

		printf(
			"     Iteration: %48.0f/%48.0f (%50.46f%%) | %.0f iter per second\n" \
			"  Current time: %56.7f secs %s\n" \
			"  Elapsed time: %56.7f secs %s\n" \
			"Estimated time: %56.7f secs %s\n",

			this->iter,
			this->max_iter,
			this->iter * 100 /this->max_iter,
			this->iter / solution_secs,

			loop_secs,
			Utils::ms_to_timestamp(loop_secs).c_str(),

			solution_secs,
			Utils::ms_to_timestamp(solution_secs).c_str(),

			predict_secs,
			Utils::ms_to_timestamp(predict_secs).c_str()
		);

		Utils::highlight_mistakes(this->sudoku);
	}
}