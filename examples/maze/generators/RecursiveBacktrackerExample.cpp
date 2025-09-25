#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <stack>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

  // // formal code
  // std::vector<bool> horizontalWalls;
  // std::vector<bool> verticalWalls;
  // //std::vector<bool> visited;
  // std::vector<Point2D> visited;
  //
  // auto sideOver2 = w->GetSize() / 2;
  //
  // std::vector<Point2D> unvisitedSides;
  // Point2D randomPoint = randomStartPoint(w);
  // std::stack<Point2D> stack;
  //
  // //visited[0] = true;
  // visited[0] = randomPoint;
  //
  // stack.push(randomPoint);
  //
  //       while (!stack.empty())
  //       {
  //           Point2D currentCell = stack.top();
  //           //int row = currentCell / width;
  //           //int col = currentCell % width;
  //
  //           // up
  //         if (currentCell.Up().y != w->GetSize()) {
  //           unvisitedSides.push_back(currentCell.Up());
  //         }
  //           // right
  //         if (currentCell.Right().x != w->GetSize()) {
  //           unvisitedSides.push_back(currentCell.Right());
  //         }
  //           // down
  //         if (currentCell.Down().y != w->GetSize()) {
  //           unvisitedSides.push_back(currentCell.Down());
  //         }
  //           // left
  //         if (currentCell.Left().x != w->GetSize()) {
  //           unvisitedSides.push_back(currentCell.Left());
  //         }
  //           if (unvisitedSides.size() == 1)
  //           {
  //               stack.push(unvisitedSides[0]);
  //               //visited[unvisitedSides[0]] = true;
  //               //visited[unvisitedSides[0]] = true;
  //
  //               int neighborRow = unvisitedSides[0] / width;
  //               int neighborCol = unvisitedSides[0] % width;
  //
  //               //up
  //               if (neighborRow < row)
  //               {
  //                   horizontalWalls[row * width + col] = false;
  //               }
  //               //right
  //               if (neighborCol > col)
  //               {
  //                   verticalWalls[row * (width + 1) + (col + 1)] = false;
  //               }
  //               //down
  //               if (neighborRow > row)
  //               {
  //                   horizontalWalls[(row + 1) * width + col] = false;
  //               }
  //               //left
  //               if (neighborCol < col)
  //               {
  //                   verticalWalls[row * (width + 1) + col] = false;
  //               }
  //           }
  //           else if (unvisitedSides.size() > 1)
  //           {
  //               size_t randomIndex = Random::next() % unvisitedSides.size();
  //               size_t randomSide = unvisitedSides[randomIndex];
  //               stack.push(randomSide);
  //               visited[randomSide] = true;
  //
  //               int neighborRow = randomSide / width;
  //               int neighborCol = randomSide % width;
  //
  //               //up
  //               if (neighborRow < row)
  //               {
  //                   horizontalWalls[row * width + col] = false;
  //               }
  //               //right
  //               if (neighborCol > col)
  //               {
  //                   verticalWalls[row * (width + 1) + (col + 1)] = false;
  //               }
  //               //down
  //               if (neighborRow > row)
  //               {
  //                   horizontalWalls[(row + 1) * width + col] = false;
  //               }
  //               //left
  //               if (neighborCol < col)
  //               {
  //                   verticalWalls[row * (width + 1) + col] = false;
  //               }
  //           }
  //           else
  //           {
  //               stack.pop();
  //           }
  //           unvisitedSides.clear();
  //       }
  // //end of formal
  // return false;


  // NOTE FOR FUTURE SELF -> COLORING THE TILES IS DONE IN WORLD
  //w->SetNodeColor()
  static std::random_device rd;
  static std::mt19937 gen(rd());

  auto sideOver2 = w->GetSize() / 2;

  if (stack.empty()) {
    Point2D startPoint = randomStartPoint(w);
    stack.push_back(startPoint);
    visited[startPoint.y][startPoint.x] = true;
    w->SetNodeColor(startPoint, Color32(255,0,0,255));
  }
  if (stack.empty()) {
    //return true;
    return false;
  }

  Point2D currentCell = stack.back();
  std::vector<Point2D> unvisitedNeighbors;
  //up
  if (currentCell.y + 1 <= sideOver2) {
    Point2D up = {currentCell.x, currentCell.y + 1};
    if (!visited[up.y][up.x]) {
      unvisitedNeighbors.push_back(up);
    }
  }

  // right
  if (currentCell.x + 1 <= sideOver2) {
    Point2D right = {currentCell.x + 1, currentCell.y};
    if (!visited[right.y][right.x]) {
      unvisitedNeighbors.push_back(right);
    }
  }

  // down
  if (currentCell.y - 1 >= -sideOver2) {
    Point2D down = {currentCell.x, currentCell.y - 1};
    if (!visited[down.y][down.x]) {
      unvisitedNeighbors.push_back(down);
    }
  }

  // left
  if (currentCell.x - 1 >= -sideOver2) {
    Point2D left = {currentCell.x - 1, currentCell.y};
    if (!visited[left.y][left.x]) {
      unvisitedNeighbors.push_back(left);
    }
  }

  if (unvisitedNeighbors.size() == 1) {
    Point2D nextCell = unvisitedNeighbors[0];
    stack.push_back(nextCell);
    visited[nextCell.y][nextCell.x] = true;
    w->SetNodeColor(nextCell, Color32(255,0,0,255));

    if (nextCell.y > currentCell.y) {
      w->SetNorth(currentCell, false);
    }
    else if (nextCell.x > currentCell.x) {
      w->SetEast(currentCell, false);
    }
    else if (nextCell.y < currentCell.y) {
      w->SetSouth(currentCell, false);
    }
    else if (nextCell.x < currentCell.x) {
      w->SetWest(currentCell, false);
    }

  }
  else if (unvisitedNeighbors.size() > 1)
    {
    std::uniform_int_distribution<size_t> dis(0, unvisitedNeighbors.size() - 1);
    size_t randomIndex = dis(gen);
    Point2D nextCell = unvisitedNeighbors[randomIndex];
    w->SetNodeColor(nextCell, Color32(255,0,0,255));
    stack.push_back(nextCell);
    visited[nextCell.y][nextCell.x] = true;
    if (nextCell.y > currentCell.y)
      {
      w->SetNorth(currentCell, false);
    }
    else if (nextCell.x > currentCell.x) {
      w->SetEast(currentCell, false);
    }
    else if (nextCell.y < currentCell.y) {
      w->SetSouth(currentCell, false);
    }
    else if (nextCell.x < currentCell.x) {
      w->SetWest(currentCell, false);
    }

  }
  else {
    w->SetNodeColor(stack.back(), Color32(0,255,0,255));
    stack.pop_back();
  }

  //return false;
  return true;

}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  // sideOver2 is made to represent 0,0. looks at clear() for how it is used
  // treat the edges as hard borders, not wrapping like previous assignment
  std::vector<Point2D> visitables;

  // todo: implement this

  // for (int y = -sideOver2; y <= sideOver2; y++) {
  //   for (int x = -sideOver2; x <= sideOver2; x++) {
  //
  //   }
  // }

  // if (p.x == -sideOver2 && p.y != -sideOver2) {
  //   visitables.push_back({p.x, p.y-1});
  //   visitables.push_back({p.x+1, p.y});
  //   visitables.push_back({p.x, p.y+1});
  // }
  // if (p.y == -sideOver2 && p.x != -sideOver2) {
  //   visitables.push_back({p.x + 1, p.y});
  //   visitables.push_back({p.x, p.y + 1});
  //   visitables.push_back({p.x - 1, p.y});
  // }
  // if (p.x == sideOver2 && p.y != sideOver2) {
  //   visitables.push_back({p.x, p.y-1});
  //   visitables.push_back({p.x-1, p.y});
  //   visitables.push_back({p.x, p.y+1});
  // }
  // if (p.y == sideOver2 && p.x != sideOver2) {
  //   visitables.push_back({p.x + 1, p.y});
  //   visitables.push_back({p.x, p.y - 1});
  //   visitables.push_back({p.x - 1, p.y});
  // }
  if (w->GetNorth(p)) {
      visitables.push_back({p.x, p.y+1});
  }
  if (w->GetEast(p)) {
    visitables.push_back({p.x+1, p.y});
  }
  if (w->GetSouth(p)) {
    visitables.push_back({p.x, p.y-1});
  }
  if (w->GetWest(p)) {
    visitables.push_back({p.x-1, p.y});
  }



  return visitables;

}
