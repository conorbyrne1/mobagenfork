#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      Point2D currentPoint(j, i);
      int neighbors = CountNeighbors(world, currentPoint);
      bool currentState = world.Get(currentPoint);

      if (currentState) {
        world.SetNext(currentPoint, neighbors == 2 || neighbors == 3);
      } else {
        world.SetNext(currentPoint, neighbors == 3);
      }
    }
  }
  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement

  int worldSize = world.SideSize();
  int alive = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      }

      int yCoord = (point.y + i + worldSize) % worldSize;
      int xCoord = (point.x + j + worldSize) % worldSize;

      Point2D neighborPoint(xCoord, yCoord);

      if (world.Get(neighborPoint)) {
        alive++;
      }
    }
  }

  return alive;
}
