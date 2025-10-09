#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
 // auto rand = Random::Range(0, 5);
  //auto pos = world->getCat();
  // switch (rand) {
  //   case 0:
  //     return World::NE(pos);
  //   case 1:
  //     return World::NW(pos);
  //   case 2:
  //     return World::E(pos);
  //   case 3:
  //     return World::W(pos);
  //   case 4:
  //     return World::SW(pos);
  //   case 5:
  //     return World::SE(pos);
  //   default:
  //     throw "random out of range";
  // }
  // std::vector path = Agent::generatePath(world);
  // return path[rand % path.size()];
  std::vector<Point2D> path = generatePath(world);

  if (!path.empty()) {
    return path[0];
  }

  auto pos = world->getCat();
  std::vector<Point2D> neighbors = World::neighbors(pos);

  for (const auto& neighbor : neighbors) {
    if (world->catCanMoveToPosition(neighbor)) {
      return neighbor;
    }
  }

  return pos;
}
