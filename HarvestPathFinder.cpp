#include "HarvestPathFinder.hpp"

#include <iostream>
#include <initializer_list>
#include <algorithm>

HarvestPathFinder::Result HarvestPathFinder::FindPath()
{
  Result result = Result();
  int rows, apple_tree_count;

  // First line
  std::cin >> rows >> apple_tree_count;

  // * This algorithm runs while it reads the data *
  //
  // For each apple_tree it evaluates the previous 3 or 2
  // values that it is connected to:
  //
  // i.e.:  OLD OLD old old
  //         | /
  //        NEW new new new
  //
  // i.e.2: OLD OLD OLD old
  //           \ | /
  //        new NEW new new
  //
  // and selects the bigger one, adding it to it's count
  // i.e:         2   4   2   2  |   2   4   2   2
  //      newLine 1   2   3   1  -> 1+4 2+4 3+4 1+2

  std::vector<int> empty;
  std::vector<std::vector<int>> apples_matrix(rows, empty);


  // First row: without evaluation
  for (int i = 0; i < apple_tree_count; ++i)
  {
    int curr;
    std::cin >> curr;
    apples_matrix[0].push_back(curr);
  }

  // Rest of rows
  for (int i = 1; i < rows; ++i)
  {
    for (int j = 0; j < apple_tree_count; ++j)
    {
      int top_tree = apples_matrix[i-1][j];

      // if FIRST, compare only TOP and TOP-RIGHT
      if (j == 0) {
        int top_right_tree = apples_matrix[i-1][j + 1];
        int curr;

        std::cin >> curr;

        apples_matrix[i].push_back(curr + std::max(top_tree, top_right_tree));
        continue;
      }

      // if LAST, compare only TOP-LEFT and TOP
      else if (j == apple_tree_count-1) {
        int top_left_tree = apples_matrix[i - 1][j - 1];
        int curr;

        std::cin >> curr;

        apples_matrix[i].push_back(curr + std::max(top_tree, top_left_tree));
        continue;
      }

      // To all others do:
      int top_left_tree = apples_matrix[i - 1][j - 1];
      int top_right_tree = apples_matrix[i-1][j + 1];
      int curr;

      std::cin >> curr;

      apples_matrix[i].push_back(curr + std::max({top_tree, top_left_tree, top_right_tree}));
    }
  }

  TracebackResult(result, apples_matrix);
  PrintResult(result);

  return result;
}

void HarvestPathFinder::TracebackResult(Result &result, const std::vector<std::vector<int>> &apples_matrix) {
  // Max of the last row is the solution's total apples
  auto max_apples_it = std::max_element(apples_matrix.back().begin(), apples_matrix.back().end());
  result.total_apples = *max_apples_it;

  int row = apples_matrix.size() - 1;
  int column = std::distance(apples_matrix.back().begin(), max_apples_it);

  result.path.push(column);

  // Traceback the path
  while(row != 0) {
    // We have three or two possible ways to go:
    // Diagonal left, up or diagonal right

    // We first select the straight up apple tree
    int max_apples = apples_matrix[row-1][column];
    int new_column = column;

    // The we test diagonals
    if (column != 0) {
      // Left diagonal
      if (max_apples < apples_matrix[row - 1][column - 1]) {
        max_apples = apples_matrix[row - 1][column - 1];
        new_column = column - 1;
      }
    }
    if (column != int(apples_matrix[0].size())-1) {
      // Right diagonal
      if (max_apples < apples_matrix[row - 1][column + 1]) {
        max_apples = apples_matrix[row - 1][column + 1];
        new_column = column + 1;
      }
    }

    result.path.push(new_column);

    column = new_column;
    row -= 1;
  }
}

void HarvestPathFinder::PrintResult(const Result& result) {
  // Print apple count


  std::stack<long long int> out = result.path;
  while (out.size() > 1) {
    std::cout << out.top() << ' ';
    out.pop();
  }
  // Print last element without space ' '
  if (!out.empty())
    std::cout << out.top() << std::endl;

  std::cout << result.total_apples << std::endl;
}
