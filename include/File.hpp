#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <variant>

std::variant<int, std::monostate> populate_input_columns(std::vector<int> &left_col, std::vector<int> &right_col, std::string &input);
std::variant<int, std::monostate> populate_reports(std::vector<std::vector<int>> &report_rows, std::string &input);

#endif // FILE_H
