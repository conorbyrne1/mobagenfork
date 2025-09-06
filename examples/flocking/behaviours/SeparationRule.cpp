#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }

// Formal code
  Vector2f accumulator = Vector2f(0, 0);
  Vector2f positionVector = Vector2f(0,0);
  Vector2f unitVector = Vector2f(0, 0);
  double magnitude = 0.0;
  int count = 0;

  for(int i = 0; i < neighborhood.size(); i++)
  {
    if (neighborhood[i] == boid)
    {
      continue;
    }
    else
    {
      positionVector = boid->getPosition() - neighborhood[i]->getPosition();
      magnitude = positionVector.getMagnitude();
      if (magnitude > 0)
      {
        unitVector = positionVector / magnitude;
      }
      if (magnitude <= desiredMinimalDistance && magnitude > 0)
      {
        accumulator += unitVector/magnitude;
        count++;
      }
    }

  }
  if (accumulator.getMagnitude() > weight)
  {
    //return (accumulator / accumulator.getMagnitude()) * maxForce;
    separatingForce = (accumulator / accumulator.getMagnitude()) * weight;
  }
  else {
    separatingForce = accumulator;
  }

  //return accumulator;

// End of formal code


  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
