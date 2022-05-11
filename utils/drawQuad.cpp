#include "drawQuad.h"

void drawQuad(float l, float h, bool wireFrame)
{
  glPushMatrix();
    glScalef(l, h, 1.0);
    if(wireFrame) {
      glBegin(GL_LINE_LOOP);
    }
    else {
      glBegin(GL_QUADS);
    }
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();
  glPopMatrix();
}
