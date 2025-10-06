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
*An easy heuristic:
(sidesize/2) - max(abs(p.x), abs(p.y))

if my size is 11, and the p is (-2, -1)
the heuristic will give me the distance to the closest border
 *
 */

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path ~~~~ came from[B] = A (left is where you came from)
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
/*
    Point2D current = frontier.front();
    frontierSet.erase(current);
    visited.at(current) = true;

    std::vector<Point2D> neighbors = w->neighbors(current);
    for (auto & neighbor : neighbors) {
      if (
        !visited.contains(neighbor) &&
        neighbor != catPos &&
        w->catCanMoveToPosition(neighbor) &&
        w->catcherCanMoveToPosition(neighbor)
        ){
        if (neighbor == borderExit) {
          break;
        }
        cameFrom.insert({current, neighbor});
        frontier.push(neighbor);
        //frontier.Enqueue(neighbor);
        frontierSet.insert(neighbor);
      }
    } */
 // https://www.redblobgames.com/pathfinding/a-star/introduction.html
    Point2D current = frontier.front();

    if (current == borderExit) {
      break;
    }

    std::vector<Point2D> neighbors = w->neighbors(current);
    for (auto neighbor : neighbors) {
      if (!cameFrom.contains(neighbor)) {
        int priority = heuristic(borderExit, neighbor);
        cameFrom.emplace(current, neighbor);
      }
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  std::vector<Point2D> path;
  for (auto & p : cameFrom) {
    path.push_back(p.first);
  }
  std::reverse(path.begin(), path.end());
  return path;
  //return vector<Point2D>();
}

// return neighbors up right down left
// neighbors need to be: not visited, not cat, not block & not in queue
// maybe make this a child function or something??
std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D* current) {
  //std::vector<Point2D> visitableNeighbors;


}

int heuristic(Point2D a, Point2D b) {
// manhattan
  return abs(a.x - b.x) + abs(a.y - b.y);
}
