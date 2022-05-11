#ifndef WAVE
#define WAVE

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#include "utils/drawVector.h"

#define M_PI 3.14159265358979323846

class Wave
{
public:
  Wave(float amplitude, float wavelength);
  float getYCor(float x, float t);
  float getSlope(float x, float t);
  void drawWave(int segments, bool wireFrame, float t);
  void drawWaveNormalLines(int segments, float t);
  bool isNormal();
  void setNormal(bool normal);
  void drawWaveTangentLines(int segments, float t);
  bool isTangent();
  void setTangent(bool normal);
private:
  float wavelength, amplitude;
  bool normalVisual = false;
  bool tangentVisual = false;
};

#endif // WAVE
