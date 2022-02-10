#pragma once

#include <stack>
#include <vector>

// From standart input, finds the best solution to the
// Rows of Apple Tree's Problem
class HarvestPathFinder
{
public:
  // Holds the result found
  struct Result {
    long long int total_apples;
    std::stack<long long int> path;
  };

  // Find's the most optimal path of the Problem
  static Result FindPath();
  // Prints the total count of apples and the indexing of thr path recorded
  static void PrintResult(const Result &result);
private:
  // From bottom to top, records the path in the Result struct
  static void TracebackResult(Result &result, const std::vector<std::vector<int>> &apples_matrix);
};
