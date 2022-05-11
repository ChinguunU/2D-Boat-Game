#ifndef PROJECTILE_STATE
#define PROJECTILE_STATE

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <string>

#include "vec2f.h"
#include "wave.h"

#define PROJ_RAD 0.01
#define G_F -0.2
#define CIRCLE_LAT_LON 32

class ProjectileState
{
public:
  ProjectileState();
  ProjectileState(ProjectileState& copy);
  void setVelocity(Vec2f v);
  void setPosition(Vec2f r);
  void setRad(float rad);
  float getRad();
  Vec2f getPosition();
  float getDefenceStartT();
  void setDefenceStartT(float t);
  void updateRadOfDefenceProjectiles(float t);
  void drawDefence();
  void drawProjectile(bool wireFrame);
  void updateProjectileStateNumerical(float dt);
  void drawTrajectoryNumerical(Wave wave, float t);
private:
  Vec3f r, v;
  float rad = PROJ_RAD;
  float defenceStartT = 0.0;
  float g = G_F;
};

typedef ProjectileState* ProjectilePtr;

#endif // PROJECTILE_STATE
