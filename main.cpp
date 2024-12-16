#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <variant>
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
        } else {
            unsafe_reports++;
        }
    }
}


int main()
{
    std::vector<int> left_col;
    std::vector<int> right_col;
    std::vector<std::vector<int>> report_rows;

    int col_size;
    int total_distance{0};
    int similarity_score{0};
    int safe_reports{0};
    int unsafe_reports{0};

    std::string columns_input = "files/input.csv";
    std::string reports_input = "files/reports.csv";

    populate_input_columns(left_col, right_col, columns_input);
    populate_reports(report_rows, reports_input);

    calculate_report_status(safe_reports, unsafe_reports, report_rows);

    sort(left_col.begin(), left_col.end());
    sort(right_col.begin(), right_col.end());

    col_size = left_col.size();

    calculate_total_distance(total_distance, left_col, right_col, col_size);
    calculate_similarity_score(similarity_score, left_col, right_col, col_size);
    std::cout << "\033[2J\033[1;1H";
    std::cout << "------------------------------------------------------------" << "\n";
    std::cout << "ADVENT OF CODE IMPLEMENTATIONS" << "\n";
    std::cout << "------------------------------------------------------------" << "\n";
    std::cout << "Total distance between both lists is equal to: " << total_distance << '\n';
    std::cout << "Similarity score calculation equals to: " << similarity_score << '\n';
    std::cout << "------------------------------------------------------------" << "\n";
    std::cout << "Unsafe reports: " << unsafe_reports << '\n';
    std::cout << "Safe reports: " << safe_reports << '\n';
    return 0;
}
