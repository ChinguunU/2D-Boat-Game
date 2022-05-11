#include "drawVector.h"

void drawVector(float x, float y, float u, float v,
                float s, bool normalize,
                float r, float g, float b) {
  float ePointX, ePointY;
  if(!normalize) {
    ePointX = x + u * s;
    ePointY = y + v * s;
  }
  else {
    float magnitude = sqrtf(powf(u, 2) + powf(v, 2));
    ePointX = x + u / (10.0 * magnitude);
    ePointY = y + v / (10.0 * magnitude);
  }

  glBegin(GL_LINES);
  glColor3f(r, g, b);
  glVertex2f(x, y);
  glVertex2f(ePointX, ePointY);
  glEnd();
}
