#include "Game.h"

void Game::main_menu()
{
    int choice;
    do
    {
        system("cls");
        std::cout << "Welcome at SUDOKU CLI game.\nCopyright (C) 2021: Simik31 / https://github.com/Simik31/Sudoku_CLI / simik31@pm.me \n\n[1] Input sudoku by hand\n[2] Load sudoku from file\n[3] Load 'default' sudoku\n\n > ";
        choice = std::cin.get() - 48;
    } while (choice < 1 || choice > 3);

    while (!this->loaded)
    {
        switch (choice)
        {
            case 1: this->load_by_hand(); break;
            case 2: this->load_from_file(); break;
            case 3: this->load_default(); break;
        }
        if (!this->loaded)
        {
            std::cout << "Press any key to repeat...";
            _getch();
        }
    }
}

void Game::load_by_hand()
{
    std::cout << "Enter sudoku by using arrows to navigate into cell and pressing corresponding number.\nWhen you are done enetering numbers, press Enter to start solving.\n\nPress any key to strart...";
    _getch();

    Utils::print_sudoku(this->sudoku);

    Sudoku tmp;

    while (true)
    {
        int fill = -1;

        MOVE_CURSOR_TO_CELL(this->cursor_x, this->cursor_y);

        int in = _getch();
        switch (in)
        {
            case KEY_ENTER: 
            {
                std::vector<int> init;
                init.reserve(81);

                for (int i = 0; i < 81; i++) init.push_back(Sudoku::get_state(tmp, i));

                this->loaded = true;

                return Utils::print_sudoku(this->sudoku = Sudoku(init));
            };
            case KEY_UP: this->cursor_y = WRAP(this->cursor_y - 1); break;
            case KEY_RIGHT: this->cursor_x = WRAP(this->cursor_x + 1); break;
            case KEY_DOWN: this->cursor_y = WRAP(this->cursor_y + 1); break;
            case KEY_LEFT: this->cursor_x = WRAP(this->cursor_x - 1); break;
            default: if (in >= 49 && in <= 57) tmp.fill_number(this->cursor_x, this->cursor_y, in - 48); // 49 = 1, 50 = 2, ... 57 = 9
        }            
    }
}

void Game::load_from_file()
{
    system("cls");
    std::cout << "Please enter file path\n\n > ";
    std::string path;
    std::cin >> path;

    std::vector<std::string> file_lines = Utils::read_lines_from_file(path);

    if (file_lines.size() == 0)
    {
        std::cerr << "File not found or empty: " << std::filesystem::absolute(path) << std::endl;
        return;
    }
    else if (file_lines.size() != 9)
    {
        std::cerr << "Sudoku must have exactly 9 lines. " << file_lines.size() << " given." << std::endl;
        return;
    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            if (file_lines[i].size() != 9)
            {
                std::cerr << "Each sudoku line must have exactly 9 columns. On line " << (i + 1) << " only " << file_lines[i].size() << " columns given." << std::endl;
                return;
            }
        }
    }

    std::vector<int> init;
    init.reserve(81);

    for (std::string line : file_lines)
        for (char c : line)
            init.push_back(c - '0');

    this->sudoku = Sudoku(init);
    this->loaded = true;
}

void Game::load_default()
{
    int state[9][9]{
        { 0, 2, 0, 0, 0, 4, 3, 0, 0 },
        { 9, 0, 0, 0, 2, 0, 0, 0, 8 },
        { 0, 0, 0, 6, 0, 9, 0, 5, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 7, 2, 5, 0, 3, 6, 8, 0 },
        { 6, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 8, 0, 2, 0, 5, 0, 0, 0 },
        { 1, 0, 0, 0, 9, 0, 0, 0, 3 },
        { 0, 0, 9, 8, 0, 0, 0, 6, 0 }
    };

    std::vector<int> init;
    for (int (&row)[9] : state) for (int cell : row) init.push_back(cell);

    this->sudoku = Sudoku(init);
    this->loaded = true;
}

void Game::run()
{
    if (!loaded) return;

    Utils::print_sudoku(this->sudoku);

    while (!this->sudoku.is_solved())
    {
        int fill = -1;

        MOVE_CURSOR_TO_CELL(this->cursor_x, this->cursor_y);

        int in = _getch();
        switch (in)
        {
        case KEY_UP: this->cursor_y = WRAP(this->cursor_y - 1); break;
        case KEY_RIGHT: this->cursor_x = WRAP(this->cursor_x + 1); break;
        case KEY_DOWN: this->cursor_y = WRAP(this->cursor_y + 1); break;
        case KEY_LEFT: this->cursor_x = WRAP(this->cursor_x - 1); break;
        default: if (in >= 49 && in <= 57)
            {
                this->sudoku.fill_number(this->cursor_x, this->cursor_y, in - 48); // 49 = 1, 50 = 2, ... 57 = 9
                this->sudoku.test_if_solved();
            }
        }

    }
}