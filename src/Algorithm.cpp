#include "Algorithm.hpp"
#include <unordered_set>
#include <vector>
#include <string>

void Algorithm::uncorrupt_memory(std::string &c_mem)
{
    // increment memory piece to avoid out of bounds
    c_mem += "#####################################";

    int answer = 0;
    const int memory_size = (int)c_mem.length();

    const int mul_length = 4;
    const int do_length = 4;
    const int dont_length = 7;

    bool enabled = true;

    auto getNumber = [&](int &i)
    {
        int x{0};

        while (x < 1000 && isdigit(c_mem[i]))
        {
            x = 10 * x + (c_mem[i] - '0');
            i++;
        }

        if (1 <= x && x <= 999)
        {
            return x;
        }

        return -1;
    };

    for (int i = 0; i < memory_size; i++)
    {
        if (c_mem.substr(i, do_length) == "do()")
        {
            enabled = true;
        }
        if (c_mem.substr(i, dont_length) == "don\'t()")
        {
            enabled = false;
        }

        if (enabled && c_mem[i] == 'm')
        {
            if (c_mem.substr(i, mul_length) == "mul(")
            {
                i += mul_length;
                int x = getNumber(i);

                if (c_mem[i] == ',')
                {
                    i += 1;

                    int y = getNumber(i);

                    if (c_mem[i] == ')')
                    {
                        if (x != -1 && y != -1)
                        {
                            answer += x * y;
                        }
                    }
                }
            }
        }
    }

    std::cout << "Total sum of mul operations: " << answer << '\n';
}

void Algorithm::grid_search(const std::vector<std::string> &xm_rows)
{
    const int HEIGHT = xm_rows.size();
    const int WIDTH = xm_rows[0].length();

    std::string word = "XMAS";
    int word_length = word.length();

    int count = 0;

    // directions to check: (row change, column change) pairs.
    std::vector<std::pair<int, int>> directions = {
        {0, 1},   // Right (horizontal)
        {0, -1},  // Left (horizontal)
        {1, 0},   // Down (vertical)
        {-1, 0},  // Up (vertical)
        {1, 1},   // Down-right (diagonal)
        {-1, -1}, // Up-left (diagonal)
        {1, -1},  // Down-left (diagonal)
        {-1, 1}   // Up-right (diagonal)
    };

    auto inbounds = [&](int &r, int &c) -> bool
    {
        return r < 0 || r >= HEIGHT || c < 0 || c >= WIDTH;
    };

    auto match = [&](int &r, int &c, int &i)
    {
        return xm_rows[r][c] != word[i];
    };

    auto checkWord = [&](int row, int col, int dirRow, int dirCol) -> bool
    {
        for (int i = 0; i < word_length; ++i)
        {
            int r = row + dirRow * i;
            int c = col + dirCol * i;

            if (inbounds(r, c) || match(r, c, i))
            {
                return false;
            }
        }

        return true;
    };

    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            for (const auto &dir : directions)
            {
                if (checkWord(row, col, dir.first, dir.second))
                {
                    ++count;
                }
            }
        }
    }

    std::cout << "Grid Search Algorithm results: " << count << '\n';
}

void Algorithm::x_grid_search(std::vector<std::string> &xm_rows)
{
    const int HEIGHT = xm_rows.size();
    const int WIDTH = xm_rows[0].length();

    int count = 0;

    std::vector<std::pair<int, int>> directions = {
        {-1, -1},
        {-1, 1},
        {1, 1},
        {1, -1},
    };

    auto match_any = [&](const std::string &s)
    {
        static const std::unordered_set<std::string> patterns = {
            "MMSS", "MSSM", "SSMM", "SMMS"};
        return patterns.count(s) > 0;
    };

    for (int row = 1; row < HEIGHT - 1; ++row)
    {
        for (int col = 1; col < WIDTH - 1; ++col)
        {
            if (xm_rows[row][col] == 'A')
            {
                std::string s;
                for (auto direction : directions)
                {
                    s += xm_rows[row + direction.first][col + direction.second];
                }

                if (match_any(s))
                    count++;
            }
        }
    }

    std::cout << "X-Grid Search Algorithm results: " << count << '\n';
}
