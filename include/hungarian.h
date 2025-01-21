#pragma once
#include <iostream>


/**
 * @brief Print matrix
 * @param matrix Matrix
 */
template <typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix)
{
    for (const auto& row : matrix)
    {
        for (const auto& element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Find the global maximum of a matrix 
 * @param matrix Matrix
 * @return Global maximum of the matrix
 */
template <typename T>
T globalMaximum(std::vector<std::vector<T>>& matrix);

/**
 * @brief Subtract the maximum value from a matrix
 * @param matrix Matrix
 */
template <typename T>
void subtractMatrixMaximum(std::vector<std::vector<T>>& matrix);

/**
 * @brief Pad rectangle matrix to square
 * @param matrix Matrix
 * @param value Padding value
 */
template <typename T>
void padMatrix(std::vector<std::vector<T>>& matrix, const T& value);

/**
 * @brief Subtract row minima
 * @param matrix Matrix
 */
template <typename T>
void subtractRowMinima(std::vector<std::vector<T>>& matrix);

/**
 * @brief Subtract column minima
 * @param matrix Matrix
 */
template <typename T>
void subtractColumnMinima(std::vector<std::vector<T>>& matrix);

/**
 * @brief Check if a matrix is empty (all elements are 0s)
 * @param matrix Matrix
 * @return Whether the matrix is empty
 */
bool isEmptyMatrix(std::vector<std::vector<int>> matrix);

/**
 * @brief Count ones in row
 * @param matrix Matrix
 * @param rowIndex Row index
 * @return Number of 0s the the row
 */
template <typename T>
size_t countOnesInRow(const std::vector<std::vector<T>>& matrix, int rowIndex);

/**
 * @brief Count ones in column
 * @param matrix Matrix
 * @param rowIndex Column index
 * @return Number of 0s the the column
 */
template <typename T>
size_t countOnesInColumn(const std::vector<std::vector<T>>& matrix, int colIndex);

/**
 * @brief Calculate the number of minimum lines to cover all 0s.
 * @param vLines Vertical cover line indices
 * @param hLines Horizontal cover line indices
 * @return Number of minimum lines to cover all 0s
 */
template <typename T>
int minimumLines(std::vector<std::vector<T>>& matrix,
                 std::vector<int>& vLines,
                 std::vector<int>& hLines);

/**
 * @brief Find the global minimum of a matrix 
 * @param matrix Matrix
 * @param vLines Column indices covered
 * @param hLines Row indices covered
 * @return Global minimum of the matrix
 */
template <typename T>
T uncoveredGlobalMinimum(std::vector<std::vector<T>>& matrix,
                         std::vector<int>& vLines,
                         std::vector<int>& hLines);

/**
 * @brief Update the matrix by subtracting the smallest uncovered value from all 
 * the uncovered elements, and add it to all the elements that are covered twice
 * @param matrix Matrix
 * @param vLines Column indices covered
 * @param hLines Row indices covered
 * @param minimumValue Smallest uncovered value
 */
template <typename T>
void updateCostMatrix(std::vector<std::vector<T>>& matrix, 
                      std::vector<int>& vLines,
                      std::vector<int>& hLines,
                      T minimumValue);

/**
 * @brief For each row, find the column that has value 0
 * @param matrix [in] Matrix
 * @param hZeros [out] Vector to store the indicies of zeros in each row
 */
template <typename T>
void findZerosInEachRow(const std::vector<std::vector<T>>& matrix, std::vector<std::vector<int>>& hZeros);

/**
 * @brief Find optimal matches
 * @param matrix [in] Matrix
 * @param matches [out] Assignment mapping, keys are row indices and values are column indices
 */
template <typename T>
void optimalMatches(std::vector<std::vector<T>>& matrix, 
                    std::unordered_map<int, int>& matches);

/**
 * @brief Hungarian algorithm
 * @param costMatrix [in] Rectangle cost matrix
 * @param maximum Set true to find maximum values
 * @param assignment [out] Optimal assignment
 * @return Cost of the assignment
 */
float hungarian(std::vector<std::vector<float>>& costMatrix, bool maximum, std::vector<int>& assignment);
