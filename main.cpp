#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <variant>
#include <regex>
#include <bits/stdc++.h>
#include "File.hpp"

void calculate_total_distance(int &total_distance, const std::vector<int> &left_col, const std::vector<int> &right_col, const int &col_size)
{
    for (int i = 0; i <= col_size; ++i)
    {
        total_distance += abs(left_col[i] - right_col[i]);
    }
}

void calculate_similarity_score(int &similarity_score, const std::vector<int> &left_col, const std::vector<int> &right_col, const int &col_size)
{
    for (int i = 0; i <= col_size; i++)
    {
        int z{0};

        for (int j = 0; j <= col_size; j++)
        {
            if (left_col[i] == right_col[j])
            {
                z++;
            }
        }

        if (z > 0)
        {
            similarity_score += left_col[i] * z;
        }
    }
}

bool is_safe_report(const std::vector<int> &row)
{
    bool increasing = false, decreasing = false;

    for (size_t i = 0; i < row.size() - 1; i++)
    {
        if (abs(row[i] - row[i + 1]) > 3)
        {
            return false;
        }

        if (row[i] == row[i + 1])
        {
            return false;
        }

        if (row[i] < row[i + 1])
            increasing = true;
        if (row[i] > row[i + 1])
            decreasing = true;

        if (increasing && decreasing)
        {
            return false;
        }
    }

    return true;
}

bool is_safe_with_one_removal(const std::vector<int> &row)
{
    for (size_t i = 0; i < row.size(); i++)
    {
        std::vector<int> modified_row = row;
        modified_row.erase(modified_row.begin() + i);

        if (is_safe_report(modified_row))
        {
            return true;
        }
    }
    return false;
}

void calculate_report_status(int &safe_reports, int &unsafe_reports, const std::vector<std::vector<int>> &report_rows)
{
    for (const auto &row : report_rows)
    {
        if (is_safe_report(row))
        {
            safe_reports++;
        }
        else if (is_safe_with_one_removal(row))
        {
            safe_reports++;
        }
        else
        {
            unsafe_reports++;
        }
    }
}

void display_results(const int &total_distance, const int &similarity_score, const int &unsafe_reports, const int &safe_reports)
{
    std::cout << "Total distance between both lists is equal to: " << total_distance << '\n';
    std::cout << "Similarity score calculation equals to: " << similarity_score << '\n';
    std::cout << "------------------------------------------------------------" << "\n";
    std::cout << "Unsafe reports: " << unsafe_reports << '\n';
    std::cout << "Safe reports: " << safe_reports << '\n';
}

#include <iostream>
#include <vector>
#include <string>

void grid_search(const std::vector<std::string> xm_rows)
{
    int n = xm_rows.size();    // grid size (assuming square grid)
    std::string word = "XMAS"; // word to search for
    int word_length = word.length();
    int count = 0;

    // directions to check: (row change, column change) pairs.
    // each zero means the index is constant, i.e 0, 1 means x(row) is locked, while y(column) grows, going side to side.
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

    // function to check if xmas exists starting from (row, col) in the given direction
    auto checkWord = [&](int row, int col, int dirRow, int dirCol) -> bool
    {
        for (int i = 0; i < word_length; ++i)
        {
            int r = row + dirRow * i;
            int c = col + dirCol * i;

            // check if the position is out of bounds
            if (r < 0 || r >= n || c < 0 || c >= n)
            {
                return false;
            }

            // check if the character matches the corresponding character in xmas as it iterates through
            if (xm_rows[r][c] != word[i])
            {
                return false;
            }
        }
        return true;
    };

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
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

void uncorrupt_memory(std::string &c_mem)
{
    int n = (int)c_mem.length();
    int answer = 0;

    c_mem += "#########################";

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

    bool enabled = true;

    for (int i = 0; i < n - 7; i++)
    {
        if (c_mem.substr(i, 4) == "do()")
        {
            enabled = true;
        }
        if (c_mem.substr(i, 7) == "don\'t()")
        {
            enabled = false;
        }

        if (enabled && c_mem[i] == 'm')
        {
            if (c_mem[i + 1] == 'u' && c_mem[i + 2] == 'l' && c_mem[i + 3] == '(')
            {
                i += 4;
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

int main()
{
    std::vector<int> left_col;
    std::vector<int> right_col;
    std::vector<std::vector<int>> report_rows;
    std::vector<std::string> xm_rows;

    std::string c_mem;
    int col_size;
    int total_distance{0};
    int similarity_score{0};
    int safe_reports{0};
    int unsafe_reports{0};

    std::string columns_input = "files/input.csv";
    std::string reports_input = "files/reports.csv";
    std::string c_mem_input = "files/corrupted.csv";
    std::string xmas_input = "files/xmas.csv";

    populate_input_columns(left_col, right_col, columns_input);
    populate_reports(report_rows, reports_input);
    copy_corrupted_memory(c_mem, c_mem_input);
    copy_xmas_input(xm_rows, xmas_input);
    std::cout << "\033[2J\033[1;1H";
    std::cout << "------------------------------------------------------------" << "\n";
    std::cout << "ADVENT OF CODE IMPLEMENTATIONS" << "\n";
    std::cout << "------------------------------------------------------------" << "\n";

    uncorrupt_memory(c_mem);
    grid_search(xm_rows);

    calculate_report_status(safe_reports, unsafe_reports, report_rows);

    sort(left_col.begin(), left_col.end());
    sort(right_col.begin(), right_col.end());

    col_size = left_col.size();

    calculate_total_distance(total_distance, left_col, right_col, col_size);
    calculate_similarity_score(similarity_score, left_col, right_col, col_size);

    display_results(total_distance, similarity_score, unsafe_reports, safe_reports);

    return 0;
}
