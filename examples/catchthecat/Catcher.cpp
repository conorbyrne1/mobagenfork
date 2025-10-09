#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  // auto side = world->getWorldSideSize() / 2;
  // for (;;) {
  //   Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
  //   auto cat = world->getCat();
  //   if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  // }
  std::vector<Point2D> catPath = generatePath(world);

  if (!catPath.empty()) {
    for (size_t i = 0; i < catPath.size() && i < 3; i++) {
      Point2D blockPos = catPath[i];
      if (world->catcherCanMoveToPosition(blockPos)) {
        return blockPos;
      }

      std::vector<Point2D> neighbors = World::neighbors(blockPos);
      for (const auto& neighbor : neighbors) {
        if (world->catcherCanMoveToPosition(neighbor)) {
          return neighbor;
        }
      }
    }
  }

  auto catPos = world->getCat();
  std::vector<Point2D> neighbors = World::neighbors(catPos);

  for (const auto& neighbor : neighbors) {
    if (world->catcherCanMoveToPosition(neighbor)) {
      return neighbor;
    }
  }

  auto side = world->getWorldSideSize() / 2;
  for (int attempts = 0; attempts < 100; attempts++) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    if (world->catcherCanMoveToPosition(p)) {
      return p;
    }
  }

  return {0, 0};
}
