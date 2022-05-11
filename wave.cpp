#include "wave.h"

Wave::Wave(float amplitude, float wavelength)
{
  this->wavelength = wavelength;
  this->amplitude = amplitude;
}

float Wave::getYCor(float x, float t)
{
  return sinf(M_PI * (2 * x / wavelength + t / 4)) * amplitude;
}

float Wave::getSlope(float x, float t)
{
  return (2 * M_PI / wavelength) *
          cosf(M_PI * (2 * x / wavelength + t / 4)) *
          amplitude;
}

void Wave::drawWave(int segments, bool wireFrame, float t)
{
  float x, y;
  float stepSize = 2.0/(float) segments;

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if(wireFrame)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  glBegin(GL_QUAD_STRIP);
  glColor4f(0.0, 1.0, 1.0, 0.5);
  for(int loop = 0; loop <= segments; ++loop)
  {
    x = -1.0 + loop * stepSize;
    y = getYCor(x, t);
    glVertex3f(x, -1.0, 0.0);
    glVertex3f(x, y, 0.0);
  }
  glEnd();

  if(wireFrame)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  glDisable( GL_BLEND );


  if(normalVisual)
  {
    drawWaveNormalLines(segments, t);
  }

  if(tangentVisual)
  {
    drawWaveTangentLines(segments, t);
  }
}

void Wave::drawWaveNormalLines(int segments, float t)
{
  float x, y;
  float stepSize = 2.0 / (float) segments;
  for(int loop = 0; loop <= segments; ++loop)
  {
    x = -1.0 + loop * stepSize;
    y = getYCor(x, t);

    drawVector(x, y, -getSlope(x, t), 1, -1, true, 0, 1, 0);
  }
}

bool Wave::isNormal()
{
  return normalVisual;
}

void Wave::setNormal(bool normal)
{
  normalVisual = normal;
}

void Wave::drawWaveTangentLines(int segments, float t)
{
  float x, y;
  float stepSize = 2.0 / (float) segments;
  for(int loop = 0; loop <= segments; ++loop) {
    x = -1.0 + loop * stepSize;
    y = getYCor(x, t);

    drawVector(x, y, 1, getSlope(x, t), -1, true, 1, 0, 0);
  }
}

bool Wave::isTangent()
{
  return tangentVisual;
}

void Wave::setTangent(bool tangent)
{
  tangentVisual = tangent;
}
