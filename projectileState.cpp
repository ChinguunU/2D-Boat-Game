#include "projectileState.h"

ProjectileState::ProjectileState()
{
  r = {0.0, 0.0};
  v = {0.0, 0.0};
}

ProjectileState::ProjectileState(ProjectileState& copy)
{
  r = copy.r;
  v = copy.v;
}

void ProjectileState::setVelocity(Vec2f v)
{
  this->v = v;
}

void ProjectileState::setPosition(Vec2f r)
{
  this->r = r;
}

void ProjectileState::setRad(float rad)
{
  this->rad = rad;
}

float ProjectileState::getRad()
{
  return rad;
}

Vec2f ProjectileState::getPosition() {
  return r;
}

float ProjectileState::getDefenceStartT()
{
  return defenceStartT;
}

void ProjectileState::setDefenceStartT(float t)
{
  defenceStartT = t;
}

void ProjectileState::updateRadOfDefenceProjectiles(float t)
{
  rad += 0.0007 * t / defenceStartT;
}

void ProjectileState::drawDefence()
{
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
    glTranslatef(r.x, r.y, 0.0);
    glutWireSphere(rad, CIRCLE_LAT_LON, CIRCLE_LAT_LON);
  glPopMatrix();
}

void ProjectileState::drawProjectile(bool wireFrame)
{
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
    glTranslatef(r.x, r.y, 0.0);
    drawCircle(PROJ_RAD, CIRCLE_LAT_LON, wireFrame);
  glPopMatrix();
}

void ProjectileState::updateProjectileStateNumerical(float dt)
{
  // Position
  r.x += v.x * dt;
  r.y += v.y * dt;

  // Velocity
  v.y += g * dt;
}

void ProjectileState::drawTrajectoryNumerical(Wave wave, float t)
{
  float dt = 0.001;

  Vec2f tempR = r;
  Vec2f tempV = v;

  glColor3f(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  while(tempR.y >= wave.getYCor(tempR.x, t) &&
        !((tempR.x >= -0.25 && tempR.x <= 0.25) && (tempR.y <= 0.25)))
  {
    tempR.x += tempV.x * dt;
    tempR.y += tempV.y * dt;

    tempV.y += g * dt;
    glVertex2f(tempR.x, tempR.y);
  }
  glEnd();
}
