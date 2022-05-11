#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include "cannon.h"
#include "boat.h"
#include "island.h"
#include "projectileState.h"
#include "wave.h"
#include "utils/drawAxes.h"
#include "utils/osd.h"
#include "utils/drawHealthBar.h"
#include "utils/gameOver.h"

#define BOATS 2

typedef struct {bool debug, animate, gameOver;
                float t, startTime;
                int tesselation;
                int frames;
                float frameRate;
                float frameRateInterval;
                float lastFrameRateT; } Global;

typedef struct {bool moveRight, moveLeft; } Movement;

typedef struct {bool rotateRight, rotateLeft; } Rotation;

typedef struct {Movement boat;
                Rotation cannon; } BoatMoveAndRotation;

class GameEngine
{
public:
  const int milli = 1000;
  GameEngine();
  ~GameEngine();
  void idle();
  void display();
  void drawHealthBars();
  void checkIfProjectileLandedInWater(bool isAttackProj);
  void checkIfGameOver();
  void checkBoatMovementAndCannonRotations();
  void checkIfDefenceProjectileExpired();
  void checkIfProjectileHasHitDefence();
  void keyboardCB(unsigned char key, int x, int y);
  void keyboardUpCB(unsigned char key, int x, int y);
private:
  Global global = {false, true, false, 0.0, 0.0, 64, 0, 0.0, 0.2, 0.0};
  BoatMoveAndRotation bMoveAndRotation[BOATS] = {{{false, false}, {false, false}},
                                                {{false, false}, {false, false}}};

  Rotation islandCannon = {false, false};

  Wave wave;
  BoatPtr boats[BOATS] = {new Boat({-0.75, 0.0}, false),
                          new Boat({0.75, 0.0}, true)};
  IslandPtr island = new Island();

  // Attack projectiles
  std::vector<ProjectileState*> projectilesInAir;

  // Defence projectiles
  std::vector<ProjectileState*> defenceProjectiles;
};

#endif // GAME_ENGINE
