#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  //code from formal - edited to fit into MoBaGEn
  Vector2f centerOfMass = Vector2f(0, 0);

  int counter = 0;

  for(int i = 0; i < neighborhood.size(); i++)
  {
    if(neighborhood[i] != boid)
    {
      centerOfMass += neighborhood[i]->getPosition();
      counter++;
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
    cohesionForce = Vector2f(forceDirection.x / magnitude, forceDirection.y / magnitude);
    return cohesionForce;
  }

  //end of formal code

  return cohesionForce;
}