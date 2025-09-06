#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"
#include <math.h>

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood


  //code from formal
  Vector2f centerOfMass = Vector2f(0, 0);
  //Boid targetBoid = boids[boidAgentIndex];
  int counter = 0;

  for(int i = 0; i < neighborhood.size(); i++)
  {
    if(neighborhood[i] != boid)
    {
      double distanceX = boid->getPosition()->X - neighborhood[i]->getPosition().x;
      double distanceY = boid->getPosition()->Y - neighborhood[i]->getPosition().y;
      double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

      if(distance <= boid->getRadius())
      {
        centerOfMass += neighborhood[i]->getPosition();
        counter++;
      }
    }
  }

  if(counter == 0) {
    return Vector2f(0, 0);
  }

  centerOfMass = centerOfMass / counter;

  Vector2f forceDirection = centerOfMass - boid->getPosition();

  double magnitude = sqrt(forceDirection.x * forceDirection.x + forceDirection.y * forceDirection.y);
  if(magnitude > 0)
  {
    Vector2f normalizedForce = Vector2f(forceDirection.x / magnitude, forceDirection.y / magnitude);
    return normalizedForce * k;
  }

  return Vector2f(0, 0);
//end of formal code

  return Vector2f::normalized(averageVelocity);
}