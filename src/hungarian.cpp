#include <algorithm>
#include <vector>
#include <numeric>

#include "hungarian.h"

#define MIN(a, b) (a <= b) ? a : b 
#define MAX(a, b) (a > b) ? a : b 


template <typename T>
T globalMaximum(std::vector<std::vector<T>>& matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    T maximum = matrix[0][0];

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (matrix[i][j] > maximum)
            {
                maximum = matrix[i][j];
            }
        }
    }

    return maximum;
}

template <typename T>
void subtractMatrixMaximum(std::vector<std::vector<T>>& matrix)
{
    if (matrix.empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    T max = globalMaximum(matrix);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = max - matrix[i][j];
        }
    }
}

template <typename T>
void padMatrix(std::vector<std::vector<T>>& matrix, const T& value)
{
    if (matrix.empty()) return;

    size_t rows = matrix.size();
    size_t columns = matrix[0].size();

    if (rows < columns)
    {
        matrix.resize(columns, std::vector<T>(columns, value));
    }
    else if (columns < rows)
    {
        for (auto& row : matrix)
        {
            row.resize(rows, value);
        }
    }
}

template <typename T>
void subtractRowMinima(std::vector<std::vector<T>>& matrix)
{
    if (matrix.empty() || matrix[0].empty()) return;

    for (std::vector<T>& row : matrix)
    {
        auto min = *std::min_element(row.begin(), row.end());
        if (min == 0) continue;

        for (auto& element : row)
        {
            element -= min;
        }
    }
}

template <typename T>
void subtractColumnMinima(std::vector<std::vector<T>>& matrix)
{
    if (matrix.empty() || matrix[0].empty()) return;

    size_t rows = matrix.size();
    size_t columns = matrix[0].size();

    for (size_t col = 0; col < columns; ++col)
    {
        T minValue = matrix[0][col];
        for (size_t row = 1; row < rows; ++row)
        {
            if (matrix[row][col] < minValue)
            {
                minValue = matrix[row][col];
            }
            if (minValue == 0) break;
        }
        if (minValue == 0) continue;

        for (size_t row = 0; row < rows; ++row)
        {
            matrix[row][col] -= minValue;
        }
    }
}

bool isEmptyMatrix(std::vector<std::vector<int>> matrix)
{
    for (std::vector<int>& row : matrix)
    {
        if (std::any_of(row.begin(), row.end(), [](int x) { return x != 0; }))
        {
            return false;
        }
    }

    return true;
}

template <typename T>
size_t countOnesInRow(const std::vector<std::vector<T>>& matrix, int rowIndex)
{
    // Ensure that the column index is valid
    if (matrix.empty() || rowIndex >= matrix[0].size()) {
        return 0;
    }

    return std::count(matrix[rowIndex].begin(), matrix[rowIndex].end(), 1);
}

template <typename T>
size_t countOnesInColumn(const std::vector<std::vector<T>>& matrix, int colIndex)
{
    size_t count = 0;

    // Ensure that the column index is valid
    if (matrix.empty() || colIndex >= matrix[0].size()) {
        return count;
    }

    // Iterate through each row and count zeros in the given column index
    for (const auto& row : matrix)
    {
        if (row[colIndex] == 1)
        {
            ++count;
        }
    }

    return count;
}

template <typename T>
int minimumLines(std::vector<std::vector<T>>& matrix,
                 std::vector<int>& vLines,
                 std::vector<int>& hLines)
{
    size_t length = matrix.size();
    std::vector<std::vector<int>> counter(length, std::vector<int>(length, 0));

    int lines = 0;

    // Count number of 0s in each row and column
    for (size_t i = 0; i < length; ++i)
    {
        for (size_t j = 0; j < length; ++j)
        {
            if (matrix[i][j] == 0)
            {
                counter[i][j] = 1;
            }
        }
    }

    // Count minimum number of lines to cover all 0s
    int numZeros;
    for (size_t i = length; (i >= 0) && (lines < (int)length) && !(isEmptyMatrix(counter)); --i)
    {
        for (size_t j = 0; j < length; ++j)
        {
            // Horizontal lines 
            numZeros = countOnesInRow(counter, j);
            if (numZeros >= i)
            {
                lines++;
                hLines.push_back(j);
                // Change all 1s in row j to 0s
                for (int k = 0; k < length; ++k)
                {
                    counter[j][k] = 0;
                }
            }
            if (isEmptyMatrix(counter)) break;
            if (lines >= (int) length) break;

            // Vertical lines 
            numZeros = countOnesInColumn(counter, j);
            if (numZeros >= i)
            {
                lines++;
                vLines.push_back(j);
                // Change all 1s in column j to 0s
                for (auto& row : counter)
                {
                    row[j] = 0;
                }
            }
            if (isEmptyMatrix(counter)) break;
            if (lines >= (int) length) break;
        }
    }

    return lines;
}

template <typename T>
T uncoveredGlobalMinimum(std::vector<std::vector<T>>& matrix,
                         std::vector<int>& vLines,
                         std::vector<int>& hLines)
{
    int length = matrix.size();
    T minimum = matrix[0][0];
    for (int i = 0; i < length; ++i)
    {
        // skip row if row is covered
        if (std::find(hLines.begin(), hLines.end(), i) != hLines.end()) continue;

        for (int j = 0; j < length; ++j)
        {
            // skip if column is covered
            if (std::find(vLines.begin(), vLines.end(), j) != vLines.end()) continue;

            if (matrix[i][j] < minimum)
            {
                minimum = matrix[i][j];
            }
        }
    }

    return minimum;
}

template <typename T>
void updateCostMatrix(std::vector<std::vector<T>>& matrix, 
                      std::vector<int>& vLines,
                      std::vector<int>& hLines,
                      T minimumValue)
{
    int length = matrix.size();
    bool rowCounted, colCounted;

    for (int i = 0; i < length; ++i)
    {
        rowCounted = std::find(hLines.begin(), hLines.end(), i) != hLines.end();

        for (int j = 0; j < length; ++j)
        {
            colCounted = std::find(vLines.begin(), vLines.end(), j) != vLines.end();
            
            if (rowCounted && colCounted)
            {
                matrix[i][j] += minimumValue;
            }
            else if (!rowCounted && !colCounted)
            {
                matrix[i][j] -= minimumValue;
            }
        }
    }
}

template <typename T>
void findZerosInEachRow(const std::vector<std::vector<T>>& matrix, std::vector<std::vector<int>>& hZeros)
{
    int numRows = matrix.size();
    int numColumns = matrix[0].size();
    for (int r = 0; r < numRows; ++r)
    {
        for (int c = 0; c < numColumns; ++c)
        {
            if (matrix[r][c] == 0)
            {
                hZeros[r].push_back(c);
            }
        }
    }
}

template <typename T>
void optimalMatches(std::vector<std::vector<T>>& matrix, 
                    std::unordered_map<int, int>& matches)
{
    int numRows = matrix.size();

    // Find the indices of zeros in each row
    std::vector<std::vector<int>> hZeros(numRows);
    findZerosInEachRow(matrix, hZeros);

    // Initialize unmatchedRows with values {0, 1, .., (length-1)}
    std::vector<int> unmatchedRows(numRows);
    std::iota(unmatchedRows.begin(), unmatchedRows.end(), 0); 
    
    int r_starred, c_starred, minNumZeros;
    while (!unmatchedRows.empty())
    {
        r_starred = unmatchedRows[0];
        minNumZeros = hZeros[unmatchedRows[0]].size();

        // Find the row with the least zeros
        for (int r : unmatchedRows)
        {
            if (hZeros[r].size() < minNumZeros)
            {
                minNumZeros = hZeros[r].size();
                r_starred = r;
            }
        }
        // Take the column index of the first 0 in the row, consider it as match
        c_starred = hZeros[r_starred][0];

        // Match
        matches[r_starred] = c_starred;

        // Remove r_starred from unmatchedRows
        auto it = std::find(unmatchedRows.begin(), unmatchedRows.end(), r_starred);
        if (it != unmatchedRows.end()) {
            unmatchedRows.erase(it);
        }

        // Update hZeros (remove c_starred from all rows)
        for (int r : unmatchedRows)
        {
            auto element = std::find(hZeros[r].begin(), hZeros[r].end(), c_starred);
            if (element != hZeros[r].end()) {
                hZeros[r].erase(element);
            }
        }
    }
}

float hungarian(std::vector<std::vector<float>>& costMatrix, bool maximum, std::vector<int>& assignment)
{
    if (costMatrix.empty() || costMatrix[0].empty()) return -1;

    // create a copy of the original cost matrix
    std::vector<std::vector<float>> originalMatrix = costMatrix;

    size_t rows = costMatrix.size();
    size_t columns = costMatrix[0].size();
    size_t paddedLength = MAX(rows, columns);

    if (maximum)
    {
        subtractMatrixMaximum(costMatrix);
    }

    // Pad if not square
    padMatrix(costMatrix, 0.0f);

    // Subtract row minima
    subtractRowMinima(costMatrix);

    // Subtract column minima
    subtractColumnMinima(costMatrix);

    int lines = 0;
    auto smallestUncoveredValue = costMatrix[0][0];
    // Initialize empty counters to handle the calculations
    std::vector<int> vLines;
    std::vector<int> hLines;
    while (lines < paddedLength)
    {
        // Find minimum horizontal and vertical lines to cover all 0s
        lines = minimumLines(costMatrix, vLines, hLines);
        
        // If number of lines equals the size of the matrix
        // match has been found
        if (lines >= paddedLength) break;

        // Find the smallest uncovered value
        smallestUncoveredValue = uncoveredGlobalMinimum(costMatrix, vLines, hLines);
        // Subtract the smallest uncovered value from all uncovered values
        // Add the value to elements that are covered twice
        updateCostMatrix(costMatrix, vLines, hLines, smallestUncoveredValue);

        vLines.clear();
        hLines.clear();
    }

    // Get the optimal matches
    std::unordered_map<int, int> matches;
    optimalMatches(costMatrix, matches);

    // Calculate cost
    float cost = 0;
    for (int r = 0; r < rows; ++r) {
        if (matches[r] >= columns)
        {
            assignment.push_back(-1);
        }
        else
        {
            assignment.push_back(matches[r]);
            cost += originalMatrix[r][matches[r]];
        }
    }

    return cost;
}
