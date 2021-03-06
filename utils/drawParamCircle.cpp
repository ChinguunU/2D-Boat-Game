#include "drawParamCircle.h"

void drawCircle(float r, int n, bool wireFrame)
{
  float x, y;
  float theta;

  glColor3f(1.0, 1.0, 1.0);
  if(wireFrame) {
    glBegin(GL_LINE_LOOP);
  }
  else {
    glBegin(GL_POLYGON);
  }

  for (int i = 0; i < n; i++) {
    theta = i / (float)n * 2.0 * M_PI;
    x = r * cosf(theta);
    y = r * sinf(theta);
    glVertex2f(x, y);
  }
  glEnd();
}
