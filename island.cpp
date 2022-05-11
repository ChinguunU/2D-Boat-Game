#include "island.h"

Island::Island()
{

}

Island::~Island()
{
  delete cannon;
}

void Island::drawIsland(bool wireFrame)
{
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0, -0.375, 0.0);
    drawQuad(0.25, 0.625, wireFrame);
    glTranslatef(0.0, 0.625, 0.0);
    glRotatef(cannon->getCannonAngle(), 0.0, 0.0, 1.0);
    glTranslatef(0.125, 0.0, 0.0);
    drawQuad(I_CANNON_LENGTH / 2.0, I_CANNON_LENGTH / 8.0, wireFrame);
  glPopMatrix();
}

void Island::updateIslandState(std::vector<ProjectileState*>& projectilesInAir)
{
  cannon->updateInitCannonVel(0.0);
  cannon->updateIslandInitCannonPos();
  cannon->checkIfFired(projectilesInAir);
}

void Island::fireCannon(float t)
{
  if(cannon->getLastFiredT() + 1 < t)
  {
    cannon->setFiring(true);
    cannon->setLastFiredT(t);
  }
}

void Island::checkIfIslandIsHit(std::vector<ProjectileState*>& projectilesInAir)
{
  unsigned int loop = 0;
  while(loop < projectilesInAir.size())
  {
    Vec2f projPos = projectilesInAir[loop]->getPosition();
    if((projPos.x >= -0.25 && projPos.x <= 0.25) && (projPos.y <= 0.25))
    {
      if(health > 0)
      {
        --health;
      }
      delete projectilesInAir[loop];
      projectilesInAir.erase(projectilesInAir.begin() + loop);
    }
    else
    {
      ++loop;
    }
  }
}

void Island::rotateCannonLeft()
{
  if(cannon->getCannonAngle() < 180.0)
  {
    cannon->setCannonAngle(cannon->getCannonAngle() + 0.5);
  }
}

void Island::rotateCannonRight()
{
  if(cannon->getCannonAngle() > 0.0)
  {
    cannon->setCannonAngle(cannon->getCannonAngle() - 0.5);
  }
}

int Island::getHealth()
{
  return health;
}
