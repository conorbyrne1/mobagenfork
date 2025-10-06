#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;
//check google chat for the function tolstenko sent
  // int heuristic(Point2D& p, int sideSizeOver2) {
  //   return std::min({sideSizeOver2 - abs(p.x), sideSizeOver2 - abs(p.y)});
  // }

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* w, Point2D* current);
  int heuristic(Point2D a, Point2D b);
};

#endif  // AGENT_H
