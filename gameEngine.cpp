#include "gameEngine.h"

GameEngine::GameEngine() : wave(0.25, 1.0)
{
  global.startTime = 0;
}

GameEngine::~GameEngine()
{
  delete island;
  for(int loop = 0; loop < BOATS; ++loop)
  {
    delete boats[loop];
  }

  for(unsigned int loop = 0; loop < projectilesInAir.size(); ++loop)
  {
    delete projectilesInAir[loop];
  }

  for(unsigned int loop = 0; loop < defenceProjectiles.size(); ++loop)
  {
    delete defenceProjectiles[loop];
  }
}

void GameEngine::idle()
{
  static float lastT = -1.0;
  float dt;

  // Check boat movement cannon rotations
  // (was done in idle to make movement of boat and rotation of cannons smoother)
  checkBoatMovementAndCannonRotations();

  // Boats position, angle update and projectiles updates
  for(int loop = 0; loop < BOATS; ++loop)
  {
    boats[loop]->updateBoatState(global.t, wave, projectilesInAir, defenceProjectiles);
  }

  // Island projectiles updates
  island->updateIslandState(projectilesInAir);

  global.t = glutGet(GLUT_ELAPSED_TIME) / (float) milli;

  if (lastT < 0.0)
  {
    lastT = global.t;
    return;
  }

  dt = global.t - lastT;
  std::cout << dt << std::endl;
  // Update state of fired projectiles
  for(unsigned int loop = 0; loop < projectilesInAir.size(); ++loop)
  {
    projectilesInAir[loop]->updateProjectileStateNumerical(dt);
  }

  // Update state of fired defence projectiles
  for(unsigned int loop = 0; loop < defenceProjectiles.size(); ++loop)
  {
    defenceProjectiles[loop]->updateProjectileStateNumerical(dt);
    defenceProjectiles[loop]->updateRadOfDefenceProjectiles(global.t);
  }

  // Check if defence projectile has expired
  checkIfDefenceProjectileExpired();

  // Check if projectile has hit defence
  checkIfProjectileHasHitDefence();

  // Checking if boat is hit
  for(int loop = 0; loop < BOATS; ++loop)
  {
    boats[loop]->checkIfBoatIsHit(projectilesInAir);
  }

  // Checking if island is hit
  island->checkIfIslandIsHit(projectilesInAir);

  // Checking if attack projectile has hit the water
  checkIfProjectileLandedInWater(true);
  checkIfGameOver();
  lastT = global.t;

  dt = global.t - global.lastFrameRateT;
  if (dt > global.frameRateInterval) {
    global.frameRate = global.frames / dt;
    global.lastFrameRateT = global.t;
    global.frames = 0;
  }
}

void GameEngine::display()
{
  int err;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawAxes(1.0);
  if(global.animate)
  {
    drawHealthBars();

    boats[0]->drawBoat(B_SCALE, 0.0, 0.0, 1.0, global.debug);
    boats[1]->drawBoat(B_SCALE, 1.0, 0.0, 0.0, global.debug);

    for(unsigned int loop = 0; loop < projectilesInAir.size(); ++loop)
    {
      projectilesInAir[loop]->drawProjectile(global.debug);
      projectilesInAir[loop]->drawTrajectoryNumerical(wave, global.t);
    }

    island->drawIsland(global.debug);

    for(unsigned int loop = 0; loop < defenceProjectiles.size(); ++loop)
    {
      defenceProjectiles[loop]->drawDefence();
    }

    wave.drawWave(global.tesselation, global.debug, global.t);

    displayOSD(global.frameRate, global.tesselation);

    if(global.gameOver) {
      displayGameOver();
    }
  }
  global.frames++;

  // Check for gl errors
  if ((err = glGetError()) != GL_NO_ERROR)
    fprintf(stderr, "Error: %s\n", gluErrorString(err));
}

void GameEngine::drawHealthBars() {
  glPushMatrix();
    glTranslatef(-0.85, 0.9, 0.0);
    drawHealthBar(boats[0]->getHealth(), MAX_B_HEALTH, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.05, 0.0);
    drawHealthBar(boats[1]->getHealth(), MAX_B_HEALTH, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.05, 0.0);
    drawHealthBar(island->getHealth(), MAX_I_HEALTH, 1.0, 1.0, 0.0);
  glPopMatrix();
}

void GameEngine::checkIfProjectileLandedInWater(bool isAttackProj)
{
  std::vector<ProjectileState*>* projectiles;
  if(isAttackProj)
  {
    projectiles = &projectilesInAir;
  }
  else
  {
    projectiles = &defenceProjectiles;
  }

  unsigned int loop = 0;
  while(loop < projectiles->size())
  {
    Vec2f projPos = (*projectiles)[loop]->getPosition();
    if(projPos.y < wave.getYCor(projPos.x, global.t))
    {
      delete (*projectiles)[loop];
      projectiles->erase(projectiles->begin() + loop);
    }
    else
    {
      ++loop;
    }
  }
}

void GameEngine::checkIfGameOver()
{
  for(int loop = 0; loop < BOATS; ++loop)
  {
    if(boats[loop]->getHealth() == 0)
    {
      global.gameOver = true;
    }
  }
  if(island->getHealth() == 0)
  {
    global.gameOver = true;
  }
}

void GameEngine::checkBoatMovementAndCannonRotations()
{

  for(int loop = 0; loop < BOATS; ++loop)
  {
    if(bMoveAndRotation[loop].boat.moveRight)
    {
      boats[loop]->moveRight();
    }
    else if(bMoveAndRotation[loop].boat.moveLeft)
    {
      boats[loop]->moveLeft();
    }

    if(bMoveAndRotation[loop].cannon.rotateRight)
    {
      boats[loop]->rotateCannonRight();
    }
    else if(bMoveAndRotation[loop].cannon.rotateLeft)
    {
      boats[loop]->rotateCannonLeft();
    }
  }

  if(islandCannon.rotateRight)
  {
    island->rotateCannonRight();
  }
  else if(islandCannon.rotateLeft)
  {
    island->rotateCannonLeft();
  }
}

void GameEngine::checkIfDefenceProjectileExpired()
{
  unsigned int loop = 0;
  while(loop < defenceProjectiles.size())
  {
    if(defenceProjectiles[loop]->getDefenceStartT() + 3 < global.t)
    {
      delete defenceProjectiles[loop];
      defenceProjectiles.erase(defenceProjectiles.begin() + loop);
    }
    else
    {
      ++loop;
    }
  }
}

void GameEngine::checkIfProjectileHasHitDefence()
{
  unsigned int loop = 0;
  while(loop < defenceProjectiles.size())
  {
    unsigned int inLoop = 0;
    while(inLoop < projectilesInAir.size())
    {
      float radA = projectilesInAir[inLoop]->getRad();
      float radD = defenceProjectiles[loop]->getRad();
      Vec2f posA = projectilesInAir[inLoop]->getPosition();
      Vec2f posD = defenceProjectiles[loop]->getPosition();
      float distance = sqrtf(powf(posA.x - posD.x, 2) + powf(posA.y - posD.y, 2));
      if(distance < radA + radD)
      {
        delete projectilesInAir[inLoop];
        projectilesInAir.erase(projectilesInAir.begin() + inLoop);
      }
      else
      {
        ++inLoop;
      }
    }

    ++loop;
  }
}

void GameEngine::keyboardCB(unsigned char key, int x, int y)
{
  if(!global.gameOver)
  {
    switch (key)
    {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      global.debug = !global.debug;
      break;
    case 'g':
      global.animate = !global.animate;
      break;
    case 'n':
      wave.setNormal(!wave.isNormal());
      break;
    case 't':
      wave.setTangent(!wave.isTangent());
      break;
    case '+':
      global.tesselation *= 2;
      break;
    case '-':
      if(global.tesselation > 4)
      {
        global.tesselation /= 2;
      }
      break;
    case 'e':
      boats[0]->fireCannon(global.t);
      break;
    case 'r':
      boats[0]->fireDefence(global.t);
      break;
    case 'q':
      bMoveAndRotation[0].cannon.rotateLeft = true;
      break;
    case 'Q':
      bMoveAndRotation[0].cannon.rotateRight = true;
      break;
    case 'a':
      bMoveAndRotation[0].boat.moveLeft = true;
      break;
    case 'd':
      bMoveAndRotation[0].boat.moveRight = true;
      break;
    case 'i':
      boats[1]->fireCannon(global.t);
      break;
    case 'u':
      boats[1]->fireDefence(global.t);
      break;
    case 'o':
      bMoveAndRotation[1].cannon.rotateRight = true;
      break;
    case 'O':
      bMoveAndRotation[1].cannon.rotateLeft = true;
      break;
    case 'j':
      bMoveAndRotation[1].boat.moveLeft = true;
      break;
    case 'l':
      bMoveAndRotation[1].boat.moveRight = true;
      break;
    case 'f':
      islandCannon.rotateLeft = true;
      break;
    case 'h':
      islandCannon.rotateRight = true;
      break;
    case ' ':
      island->fireCannon(global.t);
      break;

    default:
      break;

    }
  }
  else
  {
    switch (key)
    {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    default:
      break;
    }
  }
}

void GameEngine::keyboardUpCB(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'q':
      bMoveAndRotation[0].cannon.rotateLeft = false;
      break;
    case 'Q':
      bMoveAndRotation[0].cannon.rotateRight = false;
      break;
    case 'a':
      bMoveAndRotation[0].boat.moveLeft = false;
      break;
    case 'd':
      bMoveAndRotation[0].boat.moveRight = false;
      break;
    case 'o':
      bMoveAndRotation[1].cannon.rotateRight = false;
      break;
    case 'O':
      bMoveAndRotation[1].cannon.rotateLeft = false;
      break;
    case 'j':
      bMoveAndRotation[1].boat.moveLeft = false;
      break;
    case 'l':
      bMoveAndRotation[1].boat.moveRight = false;
      break;
    case 'f':
      islandCannon.rotateLeft = false;
      break;
    case 'h':
      islandCannon.rotateRight = false;
      break;
    default:
      break;
  }
}
