#include "Game.h"

void Game::main_menu()
{
    do
    {
        system("cls");
        std::cout << "Welcome at SUDOKU CLI game.\nCopyright (C) 2021: Simik31 / https://github.com/Simik31/Sudoku_CLI / simik31@pm.me \n\n[1] Input sudoku by hand\n[2] Load sudoku from file\n[3] Load 'default' sudoku\n\n[5] Input sudoku by hand & Brute Force solve\n[6] Load sudoku from file & Brute Force solve\n[7] Load 'default' sudoku & Brute Force solve\n\n > ";
        this->mm_choice = std::cin.get() - '0';
    } while (this->mm_choice < 1 || this->mm_choice > 7 || this->mm_choice == 4);

    while (!this->loaded)
    {
        if (this->mm_choice == 1 || this->mm_choice == 5) this->load_by_hand();
        if (this->mm_choice == 2 || this->mm_choice == 6) this->load_from_file();
        if (this->mm_choice == 3 || this->mm_choice == 7) this->load_default();

        if (!this->loaded)
        {
            std::cout << "Press any key to repeat...";
            _getch();
        }
    }
}

void Game::run()
{
    if (!this->loaded)
    {
        std::cerr << "No sudoku loaded somehow..." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (this->mm_choice < 4)
        this->solve_player();
    else
        this->solve_brute_force();
}

void Game::load_by_hand()
{
    system("cls");
    std::cout << "Enter sudoku by using arrows to navigate into cell and pressing corresponding number.\nWhen you are done enetering numbers, press Enter to start solving.\n\nPress any key to strart...";
    _getch();

    Utils::print_sudoku(this->sudoku);

    Sudoku tmp;

    while (true)
    {
        std::vector<int> init;
        init.reserve(81);

        Utils::move_cursor(this->cursor);

        int in = _getch();

        if (in == KEY_UP) this->cursor.Y = WRAP(this->cursor.Y - 1);
        else if (in == KEY_RIGHT) this->cursor.X = WRAP(this->cursor.X + 1);
        else if (in == KEY_DOWN) this->cursor.Y = WRAP(this->cursor.Y + 1);
        else if (in == KEY_LEFT) this->cursor.X = WRAP(this->cursor.X - 1);
        else if (in == KEY_ENTER)
        {
            for (int y = 0; y < 9; y++) for (int x = 0; x < 9; x++) init.push_back(Sudoku::get_state(tmp, COORD{short(x), short(y)}));
            this->sudoku = Sudoku(init);
            Utils::print_sudoku(this->sudoku);
            this->loaded = true;
            return;
        }
        else if (in >= '1' && in <= '9') tmp.fill_number(this->cursor, in - '0');
    }
}

void Game::load_from_file()
{
    system("cls");
    std::cout << "Please enter file path\n\n > ";
    std::string path;
    std::cin >> path;

    std::vector<std::string> file_lines;
    Utils::read_lines_from_file(path, file_lines);

    if (file_lines.size() == 0)
    {
        std::cerr << "File is empty: " << std::filesystem::absolute(path) << std::endl;
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

    for (std::string line : file_lines) for (char c : line) init.push_back(c - '0');

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

void Game::solve_player()
{
    Utils::print_sudoku(this->sudoku);

    while (!this->sudoku.is_solved())
    {
        Utils::move_cursor(this->cursor);

        int in = _getch();

        if (in == KEY_UP) this->cursor.Y = WRAP(this->cursor.Y - 1);
        else if (in == KEY_RIGHT) this->cursor.X = WRAP(this->cursor.X + 1);
        else if (in == KEY_DOWN) this->cursor.Y = WRAP(this->cursor.Y + 1);
        else if (in == KEY_LEFT) this->cursor.X = WRAP(this->cursor.X - 1);
        else if (in >= '1' && in <= '9')
        {
            this->sudoku.fill_number(this->cursor, in - '0');
            this->sudoku.test_if_solved();
        }
    }
}

void Game::solve_brute_force()
{
    int algo;

    do
    {
        system("cls");
        std::cout << "Select Brute Force algorithm \n\n[1] 'Stupid' algo - nonillions of universe age to solve!\n[2] Better algo - like under tenth of a second to solve\n\n > ";
        algo = std::cin.get() - '0';
    } while (algo < 1 || algo > 2);

    if (algo == 1)
        BruteForce{ this->sudoku }.solve();
    else
        BetterBruteForce{ this->sudoku }.solve();

}