#ifndef BRESENHAM_H

#define BRESENHAM_H

#include "stdSysImports.h"
using std::string;

void bresenham(int x1, int y1, int x2, int y2, string filename);
std::pair<int,int> bresenhamstep(int x1, int y1, int x2, int y2);
float slope (int x1, int y1, int x2, int y2);
std::pair<int,int> randMove (int x1, int y1, int x2, int y2);

#endif