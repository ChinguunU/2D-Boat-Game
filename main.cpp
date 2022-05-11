#include <cmath>
#include <cstdio>
#include <vector>

#include "GameEngine.h"


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GameEngine* game = new GameEngine();

void idle() {

  game->idle();
  glutPostRedisplay();
}

// Display callback
void display()
{
  game->display();
  glutSwapBuffers();
}

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboardCB(unsigned char key, int x, int y)
{
  game->keyboardCB(key, x, y);

  glutPostRedisplay();
}

void keyboardUpCB(unsigned char key, int x, int y)
{
  game->keyboardUpCB(key, x, y);

  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Assignment 1");
  glutKeyboardFunc(keyboardCB);
  glutKeyboardUpFunc(keyboardUpCB);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
}
