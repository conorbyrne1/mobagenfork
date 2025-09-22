#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

  return false;
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

  if (p.x == -sideOver2 && p.y != -sideOver2) {
    visitables.push_back({p.x, p.y-1});
    visitables.push_back({p.x+1, p.y});
    visitables.push_back({p.x, p.y+1});
  }
  if (p.y == -sideOver2 && p.x != -sideOver2) {
    visitables.push_back({p.x + 1, p.y});
    visitables.push_back({p.x, p.y + 1});
    visitables.push_back({p.x - 1, p.y});
  }
  if (p.x == sideOver2 && p.y != sideOver2) {
    visitables.push_back({p.x, p.y-1});
    visitables.push_back({p.x-1, p.y});
    visitables.push_back({p.x, p.y+1});
  }
  if (p.y == sideOver2 && p.x != sideOver2) {
    visitables.push_back({p.x + 1, p.y});
    visitables.push_back({p.x, p.y - 1});
    visitables.push_back({p.x - 1, p.y});
  }

  return visitables;

}
