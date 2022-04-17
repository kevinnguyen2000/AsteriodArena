#ifndef TYPES
#define TYPES

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdbool.h>
#include <cmath>
#include <random>
#include <sstream>

#define m1 0
#define a_key 1
#define w_key 2
#define d_key 3

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif;

#endif 