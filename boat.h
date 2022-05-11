#ifndef BOAT
#define BOAT

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>

#include "utils/drawQuad.h"
#include "utils/radDegConv.h"
#include "utils/drawAxes.h"

#include "projectileState.h"
#include "cannon.h"

#define MAX_B_HEALTH 10

class Boat
{
public:
  Boat(Vec2f boatPos, bool boatFacingLeft);
  ~Boat();
  void drawHull(bool wireFrame);
  void drawBoat(float scale, float r, float g, float b, bool wireFrame);
  void updateBoatState(float t, Wave wave,
                      std::vector<ProjectileState*>& projectilesInAir,
                      std::vector<ProjectileState*>& defenceProjectiles);
  void fireCannon(float t);
  void fireDefence(float t);
  void checkIfBoatIsHit(std::vector<ProjectileState*>& projectilesInAir);
  void rotateCannonLeft();
  void rotateCannonRight();
  void moveLeft();
  void moveRight();
  int getHealth();

private:
  float boatAngle = 0.0;
  int health = MAX_B_HEALTH;
  Vec2f boatPos;
  bool boatFacingLeft;
  CannonPtr cannon;
  float boatHitRadius = 0.5 * B_SCALE;
};

typedef Boat* BoatPtr;

#endif // BOAT
