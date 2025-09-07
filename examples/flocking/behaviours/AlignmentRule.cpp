#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood


  //code from formal - edited to fit into MoBaGEn
  Vector2f accumulator = Vector2f(0, 0);
  int count = 0;
  for(int i = 0; i < neighborhood.size(); i++)
  {
    // if (neighborhood[i] != boid) {
    //   accumulator += neighborhood[i]->getVelocity();
    //   count++;
    // }
      accumulator += neighborhood[i]->getVelocity();
      count++;

  }

  //return Vector2f(accumulator / count) * k;
  averageVelocity = accumulator / count;

//end of formal code

  return Vector2f::normalized(averageVelocity);
}