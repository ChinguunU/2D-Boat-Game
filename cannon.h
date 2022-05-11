#ifndef CANNON
#define CANNON

#include <vector>
#include <iostream>

#include "projectileState.h"
#include "utils/radDegConv.h"

// Islands cannon length
#define I_CANNON_LENGTH  0.25
// The cannons distance from the x axis
#define I_CANNONS_DIST_FROM_XAXIS 0.25
// Scale ratio of the boat
#define B_SCALE 0.11
// Cannons length
#define B_CANNON_LENGTH 0.5
// The cannons distance from the x axis
#define B_CANNONS_DIST_FROM_XAXIS 0.25
// The cannon distance from the y axis
#define B_CANNONS_DIST_FROM_YAXIS 0.5


class Cannon
{
public:
  Cannon(float cannonAngle);
  ~Cannon();
  float getCannonAngle();
  void setCannonAngle(float angle);
  float getLastFiredT();
  void setLastFiredT(float t);
  bool isFiring();
  void setFiring(bool fire);
  float getLastDefendT();
  void setLastDefendT(float t);
  bool isDefending();
  void setDefending(bool defend);
  void checkIfFired(std::vector<ProjectileState*>& projectilesInAir);
  void checkIfFiredDefence(std::vector<ProjectileState*>& defenceProjectiles, float t);
  void updateInitCannonVel(float axisTilt);
  void updateBoatInitCannonPos(Vec2f boatPos, float axisTilt, bool cannonFacingLeft);
  void updateIslandInitCannonPos();
private:
  float cannonAngle, pFireSpeed, lastFiredT, lastDefendT;
  bool fire, defend;
  ProjectilePtr projectile = new ProjectileState();
};

typedef Cannon* CannonPtr;

#endif // CANNON
