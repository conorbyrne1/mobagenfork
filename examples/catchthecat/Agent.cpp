#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

#include <algorithm>
using namespace std;

// path finding is done in agent and movement done in specific (cat/catcher)
// order of completion: agent -> cat -> catcher

/*
 from google chat about priority queue (not what I currently have)
A question about priority queues and unordered map / set

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

struct Point2D {
    int x;
    int y;

    Point2D(int x, int y) : x(x), y(y) {}

    bool operator==(const Point2D &other) const {
        return x == other.x && y == other.y;
    }
};

// if we want to use Point 2d as keys on hashtable structures such as umap and uset, you have to tell the STL how to hash Point2D
template <>
struct std::hash<Point2D> {
    std::size_t operator()(const Point2D &p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y));
    }
};

// in order to use Point2D in a priority queue, we need to wrap the Point2D and add a priority field and a comparator telling how to compare two Point2DPrioritized
struct Point2DPrioritized {
    Point2D point;
    int priority;

    Point2DPrioritized(Point2D point, int priority): point(point), priority(priority) {}

    // the < and > are reversed because we will give higher priority to the ones with less value
    bool operator<(const Point2DPrioritized &other) const {
        return priority > other.priority;
    }
};

int main() {
    // this will not work!!
    // std::priority_queue<Point2D> pq;
    // pq.push(Point2D(1,2));

    std::priority_queue<Point2DPrioritized> pq;
    // this only works because the Point2DPrioritized has the operator < defined
    pq.push({Point2D(1,2), 5});

    std::unordered_set<Point2D> visited;
    // this only work because we have created the hash<Point2D> specialization at the namespace of the std
    visited.insert(Point2D(1,2));
    // the same thing works for unordered_map
    std::unordered_map<Point2D, int> point_to_value;
    point_to_value[Point2D(1,2)] = 42;
}
 */


/*
*An easy heuristic:
(sidesize/2) - max(abs(p.x), abs(p.y))

if my size is 11, and the p is (-2, -1)
the heuristic will give me the distance to the closest border
 *
 */

std::vector<Point2D> Agent::generatePath(World* w) {
//   unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path ~~~~ came from[B] = A (left is where you came from)
//   queue<Point2D> frontier;                   // to store next ones to visit
//   unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
//   unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
//
//   // bootstrap state
//   auto catPos = w->getCat();
//   frontier.push(catPos);
//   frontierSet.insert(catPos);
//   Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
//
//   while (!frontier.empty()) {
//     // get the current from frontier
//     // remove the current from frontierset
//     // mark current as visited
//     // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
//     // iterate over the neighs:
//     // for every neighbor set the cameFrom
//     // enqueue the neighbors to frontier and frontierset
//     // do this up to find a visitable border and break the loop
//  // https://www.redblobgames.com/pathfinding/a-star/introduction.html

  //~~~~~~ this section was made with the help of Claude AI - not entirely AI made but it fixed the stuff I did wrong
  auto compare = [](pair<int, Point2D> a, pair<int, Point2D> b) {
    return a.first > b.first;
  };

  priority_queue<pair<int, Point2D>, vector<pair<int, Point2D>>, decltype(compare)> frontier(compare);
  //~~~~~~ end of section

  unordered_map<Point2D, Point2D> cameFrom;
  unordered_map<Point2D, int> costSoFar;

  auto start = w->getCat();
  auto sideSize = w->getWorldSideSize();
  auto sideOver2 = sideSize / 2;

  frontier.push({0, start});
  cameFrom[start] = Point2D::INFINITE;
  costSoFar[start] = 0;

  Point2D goal = Point2D::INFINITE;

  while (!frontier.empty()) {
    Point2D current = frontier.top().second;
    frontier.pop();

    if (w->catWinsOnSpace(current)) {
      goal = current;
      break;
    }

    // return neighbors up right down left
    // neighbors need to be: not visited, not cat, not block & not in queue

    for (auto next : World::neighbors(current)) {
      if (!w->isValidPosition(next) || w->getContent(next)) {
        continue;
      }

      int newCost = costSoFar[current] + 1;
      if (!costSoFar.contains(next) || newCost < costSoFar[next]) {
        costSoFar[next] = newCost;
        int priority = newCost + (sideOver2 - max(abs(next.x), abs(next.y)));
        frontier.push({priority, next});
        cameFrom[next] = current;
      }
    }
  }

  std::vector<Point2D> path;
  if (goal != Point2D::INFINITE) {
    Point2D current = goal;
    while (current != start) {
      path.push_back(current);
      current = cameFrom[current];
    }
    std::reverse(path.begin(), path.end());
  }

  return path;
}


// int heuristic(Point2D a, Point2D b) {
// // manhattan
//   return abs(a.x - b.x) + abs(a.y - b.y);
// }
