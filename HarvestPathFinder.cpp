#include "HarvestPathFinder.hpp"

#include "iostream"
#include <initializer_list>
#include <algorithm>

HarvestPathFinder::Result HarvestPathFinder::FindPath()
{
  Result result = Result();
  int rows, apple_tree_count;
  std::cin >> rows >> apple_tree_count;

  // * This algorithm runs while it reads the data *
  //
  // For each apple_tree it evaluates the previous 3 or 2
  // values that it is connected to
  // i.e.:  OLD OLD old old
  //        NEW new new new  (upper-case connected to uppercase)
  // i.e.2: OLD OLD OLD old
  //        new NEW new new
  // and selects the bigger one, addinG it to it's count
  // i.e: old 2 4 2 2      2 4 2 2
  //      new 1 2 3 1  ->  5 6 7 3

  std::vector<int> empty;
  std::vector<std::vector<int>> apples_matrix(rows, empty);

  // First row without evaluation
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

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < apple_tree_count; ++j)
    {
      std::cout << apples_matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return result;
}
