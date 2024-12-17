#include "File.hpp"
#include <string>
#include <iostream>
#include <variant>

std::variant<int, std::monostate> populate_input_columns(std::vector<int> &left_col, std::vector<int> &right_col, const std::string &input)
{
    std::ifstream fin(input);
    if (!fin.is_open())
    {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        int left, right;

        if (ss >> left >> right)
        {
            left_col.push_back(left);
            right_col.push_back(right);
        }
    }

    fin.close();

    return 0;
}

std::variant<int, std::monostate> populate_reports(std::vector<std::vector<int>> &report_rows, const std::string &input)
{
    std::ifstream fin(input);

    if (!fin.is_open())
    {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }

    std::string line;

    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        std::vector<int> row;
        int row_value;

        while (ss >> row_value)
        {
            row.push_back(row_value);
        }

        report_rows.push_back(row);
    }

    fin.close();

    return std::monostate{};
}

std::variant<int, std::monostate> copy_corrupted_memory(std::string &c_mem, const std::string &input)
{
    std::ifstream fin(input);

    std::string line;
    std::stringstream buffer;
    buffer << fin.rdbuf();
    c_mem = buffer.str();

    fin.close();

    return std::variant<int, std::monostate>();
}
