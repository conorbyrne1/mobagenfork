#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

#include <iostream>

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
  if (count > 0)
    averageVelocity = accumulator / count;
  //averageVelocity = accumulator / (count +0.00001); // the 0.00001 fixes any potential divide by 0 errors (shoutout james)

//end of formal code
  //std::cout << boid->getPosition().x << ", " << boid->getPosition().y << std::endl;
  return Vector2f::normalized(averageVelocity);
}