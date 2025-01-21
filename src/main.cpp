#include <vector>
#include <iostream>

#include "hungarian.h"


int main() {
    std::vector<int> assignment;
    float cost;

    // Case 1 : Square matrix
    std::vector<std::vector<float>> cost_matrix = {
        {46.f, 31.f, 89.f, 56.f, 69.f},
        {64.f, 57.f, 9.f, 44.f, 68.f},
        {51.f, 28.f, 46.f, 41.f, 61.f},
        {57.f, 22.f, 50.f, 38.f, 91.f},
        {65.f, 53.f, 73.f, 5.f, 71.f},
    };
    cost = hungarian(cost_matrix, false, assignment);
    std::cout << "Cost: " << cost << std::endl;
    for (int i = 0; i < assignment.size(); ++i)
    {
        if (assignment[i] == -1)
        {
            std::cout << "Row " << i << " is not assigned to any column" << std::endl;
        }
        else
        {
            std::cout << "Row " << i << " matched with column " << assignment[i] << std::endl;
        }
    }
    std::cout << std::endl;
    assignment.clear();

    // Case 2 : Rectangle matrix (r < c)
    std::vector<std::vector<float>> cost_matrix2 = {
        {35, 7, 97, 60, 60, 50, 66},
        {20, 91, 94, 9, 3, 78, 24},
        {65, 2, 61, 25, 79, 83, 98}
    };
    cost = hungarian(cost_matrix2, false, assignment);
    std::cout << "Cost: " << cost << std::endl;
    for (int i = 0; i < assignment.size(); ++i)
    {
        if (assignment[i] == -1)
        {
            std::cout << "Row " << i << " is not assigned to any column" << std::endl;
        }
        else
        {
            std::cout << "Row " << i << " matched with column " << assignment[i] << std::endl;
        }
    }
    std::cout << std::endl;
    assignment.clear();

    // Case 3 : Rectangle matrix (r > c)
    std::vector<std::vector<float>> cost_matrix3 = {
        {0, 83, 69},
        {77, 0, 0},
        {11, 0, 0},
        {0, 9, 98}
    };
    cost = hungarian(cost_matrix3, false, assignment);
    std::cout << "Cost: " << cost << std::endl;
    for (int i = 0; i < assignment.size(); ++i)
    {
        if (assignment[i] == -1)
        {
            std::cout << "Row " << i << " is not assigned to any column" << std::endl;
        }
        else
        {
            std::cout << "Row " << i << " matched with column " << assignment[i] << std::endl;
        }
    }
    std::cout << std::endl;
    assignment.clear();

    return 0;
}