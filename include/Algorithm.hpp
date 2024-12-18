#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <variant>

class Algorithm
{
    public:
        static void grid_search(const std::vector<std::string>& xm_rows);
        static void uncorrupt_memory(std::string &c_mem);
        static void x_grid_search(std::vector<std::string>& xm_rows);
};
    

#endif // ALGORITHM_H
