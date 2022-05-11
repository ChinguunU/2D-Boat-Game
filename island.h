#ifndef ISLAND
#define ISLAND

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>

#include "utils/drawQuad.h"
#include "cannon.h"

#define MAX_I_HEALTH 100

class Island
{
public:
  Island();
  ~Island();
  void drawIsland(bool wireFrame);
  void updateIslandState(std::vector<ProjectileState*>& projectilesInAir);
  void fireCannon(float t);
  void checkIfIslandIsHit(std::vector<ProjectileState*>& projectilesInAir);
  void rotateCannonLeft();
  void rotateCannonRight();
  int getHealth();
private:
  int health = MAX_I_HEALTH;
  CannonPtr cannon = new Cannon(90.0);
};

typedef Island* IslandPtr;

#endif // ISLAND
