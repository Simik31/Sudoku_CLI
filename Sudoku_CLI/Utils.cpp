#include "Utils.h"

void Utils::print_sudoku(const Sudoku& sudoku, const bool cls)
{
    if (cls)
	    system("cls");

	std::cout << "+=====+=====+=====+\n"; // "╔═════╦═════╦═════╗\n"

    for (int y = 0; y < 9; y++)
    {
        std::cout << "|"; // "║"

        for (int x = 0; x < 9; x++)
        {
            COORD cursor{x, y};

            if (Sudoku::get_initial(sudoku, cursor)) SET_COLOR(10);

            Sudoku::get_state(sudoku, cursor) > 0 ? std::cout << Sudoku::get_state(sudoku, cursor) : std::cout << " ";

            SET_COLOR(7);

            std::cout << "|"; // x % 3 != 2 ? "│" : "║"
        }

        if (y % 3 != 2) std::cout << "\n|-+-+-|-+-+-|-+-+-|\n";   // "\n║─┼─┼─║─┼─┼─║─┼─┼─║\n"
        else if (y < 8) std::cout << "\n|=====|=====|=====|\n";   // "\n╠═════╬═════╬═════╣\n"
        else std::cout << "\n+=====+=====+=====+\n" << std::endl; // "\n╚═════╩═════╩═════╝\n"
    }
}

void Utils::highlight_cell(Sudoku& sudoku, const COORD& cursor)
{
    if (Sudoku::get_initial(sudoku, cursor)) SET_COLOR(202);
    else SET_COLOR(199);

    Utils::move_cursor(cursor);

    std::cout << Sudoku::get_state(sudoku, cursor);

    SET_COLOR(7);
}

void Utils::read_lines_from_file(const std::string& filename, std::vector<std::string>& lines)
{
    std::ifstream file{ std::filesystem::absolute(filename) };

    if (!file.is_open())
    {
        std::cerr << "File not found: " << std::filesystem::absolute(filename) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (getline(file, line))
        lines.push_back(line);
}

void Utils::move_cursor(const COORD& cursor)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ short(cursor.X * 2 + 1), short(cursor.Y * 2 + 1) });
}

std::string Utils::ms_to_timestamp(const double& secs)
{
    char buffer[1024];

    sprintf_s(
        buffer,
        1024,
        "[%40s universe age | %14s years | %3.0f days | %02.0f:%02.0f:%06.3f]",
        Utils::format_comas(secs / 436117076900000000, 0).c_str(),
        Utils::format_comas(std::fmod(secs / 31536000, 436117076900000000.0 / 31536000), 0).c_str(),
        std::fmod(secs / 86400, 365),
        std::fmod(secs / 3600, 24),
        std::fmod(secs / 60, 60),
        std::fmod(secs, 60)
    );

    return std::string{ buffer };
}

void Utils::highlight_mistakes(Sudoku& sudoku)
{
    if (!sudoku.is_filled()) return;

    for (short y = 0; y < 9; y++)
        for (short x1 = 0; x1 < 8; x1++)
            for (short x2 = x1 + 1; x2 < 9; x2++)
                if (Sudoku::get_state(sudoku, COORD{ x1, y }) == Sudoku::get_state(sudoku, COORD{ x2, y }))
                {
                    Utils::highlight_cell(sudoku, COORD{ x1, y });
                    Utils::highlight_cell(sudoku, COORD{ x2, y });
                }

    for (short x = 0; x < 9; x++)
        for (short y1 = 0; y1 < 8; y1++)
            for (short y2 = y1 + 1; y2 < 9; y2++)
                if (Sudoku::get_state(sudoku, COORD{ x, y1 }) == Sudoku::get_state(sudoku, COORD{ x, y2 }))
                {
                    Utils::highlight_cell(sudoku, COORD{ x, y1 });
                    Utils::highlight_cell(sudoku, COORD{ x, y2 });
                }

    short s3 = 3;

    for (short y = 0; y < 3; y++)
        for (short x = 0; x < 3; x++)
            for (short oY1 = 0; oY1 < 3; oY1++)
                for (short oX1 = 0; oX1 < 3; oX1++)
                    for (short oY2 = 0; oY2 < 3; oY2++)
                        for (short oX2 = 0; oX2 < 3; oX2++)
                            if ((oX1 == oX2 && oY1 == oY2) == false)
                                if (Sudoku::get_state(sudoku, COORD{ x * s3 + oX1, y * s3 + oY1 }) == Sudoku::get_state(sudoku, COORD{ x * s3 + oX2, y * s3 + oY2 }))
                                {
                                    Utils::highlight_cell(sudoku, COORD{ x * s3 + oX1, y * s3 + oY1 });
                                    Utils::highlight_cell(sudoku, COORD{ x * s3 + oX2, y * s3 + oY2 });
                                }
}

std::string Utils::format_comas(const double& value, const int precision)
{
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss.precision(precision);
    ss << std::fixed << value;
    return ss.str();
}