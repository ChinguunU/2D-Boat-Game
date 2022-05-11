#include "cannon.h"

Cannon::Cannon(float cannonAngle)
{
  this->cannonAngle = cannonAngle;
  pFireSpeed = 1;
  lastFiredT = 0.0;
  lastDefendT = 0.0;
  fire = false;
  defend = false;
}

Cannon::~Cannon()
{
  delete projectile;
}

float Cannon::getCannonAngle()
{
  return cannonAngle;
}

void Cannon::setCannonAngle(float angle)
{
  cannonAngle = angle;
}

float Cannon::getLastFiredT()
{
  return lastFiredT;
}

void Cannon::setLastFiredT(float t)
{
  lastFiredT = t;
}

bool Cannon::isFiring()
{
  return fire;
}

void Cannon::setFiring(bool fire)
{
  this->fire = fire;
}

float Cannon::getLastDefendT()
{
  return lastDefendT;
}

void Cannon::setLastDefendT(float t)
{
  lastDefendT = t;
}

bool Cannon::isDefending()
{
  return defend;
}

void Cannon::setDefending(bool defend)
{
  this->defend = defend;
}

void Cannon::checkIfFired(std::vector<ProjectileState*>& projectilesInAir)
{
  if(fire)
  {
    projectilesInAir.push_back(new ProjectileState(*projectile));

    fire = false;
  }
}

void Cannon::checkIfFiredDefence(std::vector<ProjectileState*>& defenceProjectiles, float t)
{
  if(defend)
  {
    defenceProjectiles.push_back(new ProjectileState(*projectile));
    defenceProjectiles[defenceProjectiles.size() - 1]->setDefenceStartT(t);
    defend = false;
  }
}

void Cannon::updateInitCannonVel(float axisTilt)
{
  Vec2f v;
  v.x = pFireSpeed * cosf(degToRad(cannonAngle)  + axisTilt);
  v.y = pFireSpeed * sinf(degToRad(cannonAngle)  + axisTilt);

  projectile->setVelocity(v);
}

void Cannon::updateBoatInitCannonPos(Vec2f boatPos, float axisTilt, bool boatFacingLeft)
{
  float bL;
  if(boatFacingLeft)
  {
    bL = -1.0;
  }
  else
  {
    bL = 1.0;
  }

  Vec2f endOfCannon;
  endOfCannon.y = B_SCALE * (B_CANNONS_DIST_FROM_XAXIS +
                  B_CANNON_LENGTH * sinf(degToRad(cannonAngle)));

  endOfCannon.x = B_SCALE * (bL * B_CANNONS_DIST_FROM_YAXIS +
                  B_CANNON_LENGTH * cosf(degToRad(cannonAngle)));

  Vec2f r;
  r.y = endOfCannon.y * cosf(axisTilt) +
        endOfCannon.x * sinf(axisTilt) + boatPos.y;

  r.x = endOfCannon.x * cosf(axisTilt) -
        endOfCannon.y * sinf(axisTilt) + boatPos.x;

  projectile->setPosition(r);
}

void Cannon::updateIslandInitCannonPos()
{
  Vec2f r;
  r.y = I_CANNONS_DIST_FROM_XAXIS +
        I_CANNON_LENGTH * sinf(degToRad(cannonAngle));

  r.x = I_CANNON_LENGTH * cosf(degToRad(cannonAngle));

  projectile->setPosition(r);
}
