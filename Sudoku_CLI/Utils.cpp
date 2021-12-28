#include "Utils.h"

void Utils::print_sudoku(const Sudoku& sudoku)
{
	system("cls");

	std::cout << "+=====+=====+=====+\n"; // "╔═════╦═════╦═════╗\n"

    for (int y = 0; y < 9; y++)
    {
        std::cout << "|"; // "║"

        for (int x = 0; x < 9; x++)
        {
            if (Sudoku::get_initial(sudoku, y * 9 + x)) SET_COLOR(10);

            Sudoku::get_state(sudoku, y * 9 + x) > 0 ? std::cout << Sudoku::get_state(sudoku, y * 9 + x) : std::cout << " ";

            SET_COLOR(7);

            std::cout << "|"; // x % 3 != 2 ? "│" : "║"
        }

        if (y % 3 != 2) std::cout << "\n|-+-+-|-+-+-|-+-+-|\n";   // "\n║─┼─┼─║─┼─┼─║─┼─┼─║\n"
        else if (y < 8) std::cout << "\n|=====|=====|=====|\n";   // "\n╠═════╬═════╬═════╣\n"
        else std::cout << "\n+=====+=====+=====+\n" << std::endl; // "\n╚═════╩═════╩═════╝\n"
    }
}

void Utils::highlight_cell(Sudoku& sudoku, const int x, const int y)
{
    if (Sudoku::get_initial(sudoku, y * 9 + x)) SET_COLOR(202);
    else SET_COLOR(199);

    MOVE_CURSOR_TO_CELL(x, y);

    std::cout << Sudoku::get_state(sudoku, y * 9 + x);

    SET_COLOR(7);
}

std::vector<std::string> Utils::read_lines_from_file(const std::string& filename)
{
    std::ifstream file{ std::filesystem::absolute(filename) };
    std::vector<std::string> lines;
    std::string line;

    if (file.is_open())
        while (getline(file, line))
            lines.push_back(line);

    return lines;
}