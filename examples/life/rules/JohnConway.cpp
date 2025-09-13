#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

// formal code
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      //int neighbors = countNeighbors(i, j);
      int neighbors = CountNeighbors(world, world.Get());
      bool currentState = cell[i][j];
      if (currentState) {
        world.setCurrent(i, j, neighbors == 2 || neighbors == 3);
      } else {
        set(i, j, neighbors == 3);
      }
    }
  }
  swapBuffer();
  //end of formal code

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement

int worldSize = world.SideSize();

// formal code
  int alive = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      }

      int yCoord = (y + i + lines) % lines;
      int xCoord = (x + j + columns) % columns;

      if (cell[yCoord][xCoord]) {
        alive++;
      }
    }
  }
  return alive;
// end of formal code
  return 0;
}
