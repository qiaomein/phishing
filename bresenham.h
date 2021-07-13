#ifndef BRESENHAM_H

#define BRESENHAM_H

#include "stdSysImports.h"
using std::string;

void bresenham(int x1, int y1, int x2, int y2, string filename);
//takes two points and creates a csv using bresenham

std::pair<int,int> bresenhamstep(int x1, int y1, int x2, int y2);
//returns the next bresenham step given two points 

float slope (int x1, int y1, int x2, int y2);
//duh

std::pair<int,int> randMove (int x1, int y1);
//returns a random move according to phishing scheme

string zone (int x, int y);
// returns the zone we are in given x,y

float findEntropy(int timesteps, std::pair<int,int> boatpositions[]);

#endif