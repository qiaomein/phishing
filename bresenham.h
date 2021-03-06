#ifndef BRESENHAM_H

#define BRESENHAM_H

#include "stdSysImports.h"
using std::string;
using std::pair;
using std::vector;

void bresenham(int x1, int y1, int x2, int y2, string filename);
//takes two points and creates a csv using bresenham

vector<pair<int,int>> bresenhamstep(std::pair<int,int> u, std::pair<int,int> v, int steps);
//returns the list of bresenham step given two points 

float slope (int x1, int y1, int x2, int y2);
//duh

std::pair<int,int> randMove (int x1, int y1);
//returns a random move according to phishing scheme

string zone (int x, int y);
// returns the zone we are in given x,y

float findEntropy(int timesteps, std::pair<int,int> boatpositions[]);
// returns the entropy from array of boat positions

float findEntropyBuffer(int buffersize, int timesteps, std::pair<int,int> boatpositions[]);
// returns the entropy from array of boat positions


std::pair<int, int> randFollowMove(int curX, int curY, int goalX, int goalY);
// return next randfollowmove given two points

void doFollowing(int n, int timesteps, int buffersize, string filename);
// makes csv file of following algo with filename

#endif