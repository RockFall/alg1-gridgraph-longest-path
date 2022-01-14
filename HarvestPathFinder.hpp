#pragma once

#include <vector>



class HarvestPathFinder
{
public:
  struct Result {
    int total_apples;
    std::vector<int> path;
  };

  static Result FindPath();

private:


};
