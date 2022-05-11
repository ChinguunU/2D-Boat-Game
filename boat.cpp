#include "boat.h"

Boat::Boat(Vec2f boatPos, bool boatFacingLeft)
{
  this->boatPos = boatPos;
  this->boatFacingLeft = boatFacingLeft;
  float cannonAngle = 30.0;
  if(boatFacingLeft)
  {
    cannonAngle = 150.0;
  }

  this->cannon = new Cannon(cannonAngle);
}

Boat::~Boat()
{
  delete cannon;
}

void Boat::drawHull(bool wireFrame)
{
  if(wireFrame)
  {
    glBegin(GL_LINE_LOOP);
  }
  else
  {
    glBegin(GL_QUADS);
  }
  glVertex2f(-0.5, -0.25);
  glVertex2f(0.5, -0.25);
  glVertex2f(1.0, 0.25);
  glVertex2f(-1.0, 0.25);
  glEnd();
}

void Boat::drawBoat(float scale,
            float r, float g, float b,
            bool wireFrame)
  {
  float bL;
  // For inverting the cannon
  if(boatFacingLeft)
  {
    bL = -1.0;
  }
  else
  {
    bL = 1.0;
  }

  glEnable(GL_DEPTH_TEST);
  glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glTranslatef(boatPos.x, boatPos.y, 0.0);
    glScalef(scale, scale, 1.0);
    glRotatef(radToDeg(boatAngle), 0.0, 0.0, 1.0);
    drawAxes(1.0);
    glColor3f(r, g, b);
    drawHull(wireFrame);
    glTranslatef(0.0, 0.5, 0.0);
    drawQuad(0.25, 0.25, wireFrame);
    glTranslatef(bL * 0.5, -0.25, 0.0);
    glRotatef(cannon->getCannonAngle(), 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    drawQuad(B_CANNON_LENGTH / 2.0, B_CANNON_LENGTH / 8.0, wireFrame);
  glPopMatrix();
  glDisable(GL_DEPTH_TEST);
}

void Boat::updateBoatState(float t, Wave wave,
                          std::vector<ProjectileState*>& projectilesInAir,
                          std::vector<ProjectileState*>& defenceProjectiles)
{
  float x = boatPos.x;
  boatPos.y = wave.getYCor(x, t);
  boatAngle = atanf(wave.getSlope(x, t));

  // Boats cannon update
  cannon->updateInitCannonVel(boatAngle);
  cannon->updateBoatInitCannonPos(boatPos, boatAngle, boatFacingLeft);
  cannon->checkIfFired(projectilesInAir);
  cannon->checkIfFiredDefence(defenceProjectiles, t);
}

void Boat::fireCannon(float t)
{
  if(cannon->getLastFiredT() + 1 < t)
  {
    cannon->setFiring(true);
    cannon->setLastFiredT(t);
  }
}

void Boat::fireDefence(float t)
{
  if(cannon->getLastDefendT() + 1 < t)
  {
    cannon->setDefending(true);
    cannon->setLastDefendT(t);
  }
}

void Boat::checkIfBoatIsHit(std::vector<ProjectileState*>& projectilesInAir)
{
  unsigned int loop = 0;
  while(loop < projectilesInAir.size())
  {
    Vec2f projPos = projectilesInAir[loop]->getPosition();
    float distance = sqrtf(pow(projPos.x - boatPos.x, 2) + pow(projPos.y - boatPos.y, 2));
    if(distance < PROJ_RAD + boatHitRadius)
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

void Boat::rotateCannonLeft()
{
  if(cannon->getCannonAngle() < 180.0)
  {
    cannon->setCannonAngle(cannon->getCannonAngle() + 0.5);
  }
}

void Boat::rotateCannonRight()
{
  if(cannon->getCannonAngle() > 0.0)
  {
    cannon->setCannonAngle(cannon->getCannonAngle() - 0.5);
  }
}

void Boat::moveLeft()
{
    float leftBound;
    if(boatFacingLeft)
    {
      leftBound = 0.25 + boatHitRadius;
    }
    else
    {
      leftBound = -1 + boatHitRadius;
    }

    if(boatPos.x > leftBound)
    {
      boatPos.x -= 0.005;
    }
}

void Boat::moveRight()
{
  float rightBound;
  if(boatFacingLeft)
  {
    rightBound = 1 - boatHitRadius;
  }
  else
  {
    rightBound = -0.25 - boatHitRadius;
  }

  if(boatPos.x < rightBound)
  {
    boatPos.x += 0.005;
  }
}

int Boat::getHealth()
{
  return health;
}
