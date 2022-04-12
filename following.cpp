#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>	
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <climits>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "bresenham.h"

using namespace std;
#define LL long long


int victim_speed = 10; 


/*
int curVictimX = 1000,curVictimY = 1000;
int lastVictimX = curVictimX-1, lastVictimY = curVictimY; // change as needed
*/

bool invis = false;

/*
float slope(int x1, int y1, int x2, int y2)
{
	return float((y2 - y1)) / (x2 - x1);
}

bool inRed(int curX, int curY)
{
	if (curX >= 1792 && curX <= 2304)
	{
		if (curY >= 1792 && curY <= 2304)
		{
			return true;
		}
	}
	return false;
}

std::pair<int, int> bresenham1step(int x1, int y1, int x2, int y2) // for slopes <= 1
{

	int o45 = 0, o8 = 0;

	if (x2 - x1 < 0 && y2 - y1>0) {
		x2 += 2 * (x1 - x2);
		o45 = 1;

	}
	else if (x2 - x1 < 0 && y2 - y1 < 0) {
		x2 += 2 * (x1 - x2);
		y2 += 2 * (y1 - y2);
		o45 = 1;
		o8 = 1;
	}
	else if (x2 - x1 > 0 && y2 - y1 < 0) {
		y2 += 2 * (y1 - y2);
		o8 = 1;
	}

	std::pair<int, int> temp = { x1,y1 };

	int m_new = 2 * (y2 - y1);
	int slope_error_new = m_new - (x2 - x1);
	for (int x = x1, y = y1, i = 0; x <= x2 && i < 2; x++, i++)
	{
		//std::cout << "(" << x - o45*(2*(x-x1)) << "," << y - o8*(2*(y-y1)) << ")\n";
		//myfile << std::to_string(x - o45*(2*(x-x1))) + ", " + std::to_string(y - o8*(2*(y-y1))) + "\n";
		temp = { x - o45 * (2 * (x - x1)),y - o8 * (2 * (y - y1)) };

		// Add slope to increment angle formed
		slope_error_new += m_new;

		// Slope error reached limit, time to
		// increment y and update slope error.
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * (x2 - x1);
		}

	}
	return temp;
}

std::pair<int, int> bresenham2step(int x1, int y1, int x2, int y2) //for reflected slopes of > 1
{


	int o36 = 0, o7 = 0;

	if (x2 - x1 < 0 && y2 - y1>0) {
		x2 += 2 * (x1 - x2);
		o36 = 1;
	}
	else if (x2 - x1 < 0 && y2 - y1 < 0) {
		x2 += 2 * (x1 - x2);
		y2 += 2 * (y1 - y2);
		o36 = 1;
		o7 = 1;
	}
	else if (x2 - x1 > 0 && y2 - y1 < 0) {
		y2 += 2 * (y1 - y2);
		o7 = 1;
	}

	std::pair<int, int> temp = { x1,y1 };

	int m_new = 2 * (x2 - x1);
	int slope_error_new = m_new - (y2 - y1);
	for (int x = x1, y = y1, i = 0; y <= y2 && i < 2; y++, i++)
	{
		//std::cout << "(" << x - o36*(2*(x-x1)) << "," << y - o7*(2*(y-y1)) << ")\n";
		//myfile << std::to_string(x - o36*(2*(x-x1))) + ", " + std::to_string(y - o7*(2*(y-y1))) + "\n";
		temp = { x - o36 * (2 * (x - x1)), y - o7 * (2 * (y - y1)) };
		// Add slope to increment angle formed
		slope_error_new += m_new;

		// Slope error reached limit, time to
		// increment y and update slope error.
		if (slope_error_new >= 0)
		{
			x++;
			slope_error_new -= 2 * (y2 - y1);
		}

	}
	return temp;
}

std::pair<int, int> bresenhamstep(int x1, int y1, int x2, int y2) {
	if (x1 == x2) {
		
		int dir = (y2 - y1) / abs(y2 - y1);
		return { x1,y1 + dir };
	}
	else {
		float m = slope(x1, y1, x2, y2);

		if (abs(m) <= 1) {
			return bresenham1step(x1, y1, x2, y2);
		}
		else {
			return bresenham2step(x1, y1, x2, y2);
		}
	}
}

std::pair<int, int> randMove(int x, int y) // note: x is positive towards right, y is positive downwards
{

	int gen = rand() % 10 + 1;
	if (gen == 1)
	{
		// northwest
		x--; y--;
	}
	if (gen == 2)
	{
		// north
		y--;
	}
	if (gen == 3) {
		// northeast
		x++;  y--;
	}
	if (gen == 4)
	{
		//west
		x--;
	}
	if (gen == 5)
	{
		//stay still
	}
	if (gen == 6)
	{
		// east
		x++;
	}
	if (gen == 7)
	{
		// southwest
		x--; y++;
	}
	if (gen == 8)
	{
		//south
		y++;
	}
	if (gen == 9)
	{
		// southeast
		x++; y++;
	}
	if (gen == 10)
	{
		// invisible
		// invis = true;
	}

	if (x < 0 || x > 4096 || y < 0 || y > 4096)
		return randMove(x, y);
	else
		return { x,y };
}
float findEntropy (int timesteps, std::pair<int,int> boatpositions[]) {
	int dx,dy;
	int p[9] = {}; //0-8 each index represents a move (not accounting for invis yet)

	//loop through the position array to create probability array
    for (int i = 1; i <= timesteps; i ++){
		dx = boatpositions[i].first - boatpositions[i-1].first;
		dy = boatpositions[i].second - boatpositions[i-1].second;
		
		if (dx == 1){
			if (dy == 1){
				p[2] = p[2] + 1;
			}
			else if (dy == -1){
				p[4]++;
			}
			else{
				p[3]++;
			}
		}
		else if (dx == -1){
			if (dy == 1){
				p[8] ++;
			}
			else if (dy == -1){
				p[6]++;
			}
			else{
				p[7]++;
			}
		}
		else if (dx == 0){
			if (dy == 1){
				p[1] ++;
			}
			else if (dy == -1){
				p[5]++;
			}
			else{
				p[0]++;
			}
		}
		
		//std::cout << dx << ',' << dy<< std::endl;
    }
	for (int i = 0; i <= 8;i++){
	//std::cout<< "p array:" << p[i] <<std::endl;
	}
	float H = 0; float P;
	for (int j = 0; j <= 8; j++){
		P = p[j]/float(timesteps);
		if (P == 0){
			continue;
		}
		//std::cout<< "probability: " << P << std::endl;
		H += P*log2(1/P);
	}
	return H;

}

float findEntropyBuffer (int buffersize, int timesteps, std::pair<int,int> boatpositions[]) {
	float H; float sum = 0; int counter = 0;
	pair<int,int> slicedPos[buffersize];

	for (int t = 0; t+buffersize < timesteps; t++){ //iterate over timesteps in boatpositions
	
		for (int i = 0; i < buffersize; i++){//iterate of history buffer
			
			slicedPos[i] = boatpositions[t+i];
			
		}

		H = findEntropy(buffersize,slicedPos);
		//cout << H << " " << t << endl;
		sum += H;
		counter ++;

		if (slicedPos[buffersize-1].first == -1){
			break;
		}
	}
	return sum/counter;

}
*/


pair<int, int> victimMover(int goalX, int goalY)
{
	return make_pair(goalX + 1, goalY); // or something else
}

bool behind(int curX, int curY, int curVictimX, int curVictimY)
{
	int lastVictimX = curVictimX-1, lastVictimY = curVictimY; // because only going to the right


	// line demarcating what is behind is the line perpendicular
	// to the last move of the victim boat

	// line of last move is y = ax+b
	// line of perpendicular is y = cx+d

	double a = (curVictimY - lastVictimY) / (curVictimX - lastVictimX);
	if (a == 0.0)
	{
		pair<double, double> uPrime;
		uPrime.first = 2*curVictimX - curX;
		uPrime.second = curY;

		double distUPrime = sqrt((uPrime.first - lastVictimX) * (uPrime.first - lastVictimX)
			+ (uPrime.second - lastVictimY) * (uPrime.second - lastVictimY));
		double distU = sqrt((curX - lastVictimX) * (curX - lastVictimX)
			+ (curY - lastVictimY) * (curY - lastVictimY));

		if (distUPrime > distU)
			return true; // currently behind
		else
			return false;
	}
	else
	{
		double c = (-1) / a;
		double b = curVictimY - a * curVictimX;
		double d = curVictimY - c * curVictimX;

		//reflect boat U over line y=cx+d
		pair<double, double> uPrime;

		// perp line from U to perp line of curV will be y = ax+e
		double e = curY - a * curX;

		//find intersection of y = ax+e and y = cx+d
		uPrime.first = (d - e) / (a - c);
		uPrime.second = a * uPrime.first + e;

		// determine distance from U points to lastVictimX,Y
		double distUPrime = sqrt((uPrime.first - lastVictimX) * (uPrime.first - lastVictimX)
			+ (uPrime.second - lastVictimY) * (uPrime.second - lastVictimY));
		double distU = sqrt((curX - lastVictimX) * (curX - lastVictimX)
			+ (curY - lastVictimY) * (curY - lastVictimY));

		if (distUPrime > distU)
			return true; // currently behind
		else
			return false;
	}
}


/*
pair<int, int> moveBehind(int curX, int curY)
{
	// trying to loop around the victim, so chooses move that stays equidistant from victim
	vector<pair<int, int>> moveList;
	for (int i = -1; i < 1; i++) // NOTE: SINCE THIS SIM ONLY HAS RIGHT TRAVELLING BOAT V, LIMITED THE ROUNDABOUT
									// SO I DONT HAVE TO HAVE A GIANT IF STATEMENT, BUT IF BOAT V MOVEMENT CHANGES THEN IT IS NEEDED
	{
		for (int j = -1; j <= 1; j++)
		{
			if (!(i == 0 && j == 0))
			{
				moveList.push_back(make_pair(i, j));
				moveList.push_back(make_pair(i, j));
			}
		}
	}

	

	double curDist = sqrt((curVictimY - curY)*(curVictimY - curY) + (curVictimX - curX)*(curVictimX - curX));
	double minDistAway = 1000000; // away from the curDist
	pair<int, int> returnMove;
	for (auto i : moveList)
	{
		// calc distance after move
		// find one closest to cur distance
		double temp = sqrt((curVictimY - (curY + i.second))*(curVictimY - (curY + i.second))
			+ (curVictimX - (curX + i.first))*(curVictimX - (curX + i.first)));
		if (abs(curDist-temp) < minDistAway)
		{
			minDistAway = abs(curDist - temp);
			returnMove = i;
		}
	}
	return returnMove;
}

pair<int, int> zigzag(int curX, int curY)
{
	// zigzag
	int i = 15 + rand() % 10;

	// randomly choose a cardinal direction to zig zag in
	int direction = rand() % 4 + 1;
	pair<int, int> move1, move2, move3 = { 0,0 };
	if (direction == 1)
	{
		// north
		move1 = { -1,1 };
		move2 = { 1,1 };
	}
	if (direction == 2)
	{
		// south
		move1 = { -1,-1 };
		move2 = { 1,-1 };
	}
	if (direction == 3)
	{
		// east
		move1 = { 1,-1 };
		move2 = { 1,1 };
	}
	if (direction == 4)
	{
		// west
		move1 = { -1,-1 };
		move2 = { -1,1 };
	}

	int j = 0;
	bool failure = false;
	while (j < i)
	{
		int segmentLength = i / 5 + rand() % 3 - 1;
		j += segmentLength;
		if (j > i)
			segmentLength -= j - i;

		int randMoveType = rand() % 3 + 1;
		pair<int, int> curMove;
		if (randMoveType == 1)
			curMove = move1;
		else if (randMoveType == 2)
			curMove = move2;
		else if (randMoveType == 3)
			curMove = move3;

		for (int k = 0; k < segmentLength; k++)
		{
			int x = curX; int y = curY;

			x += curMove.first; y += curMove.second;

			if (x < 0 || x > 4096 || y < 0 || y > 4096)
			{
				failure = true;
				break;
			}
			else
			{
				curX = x; curY = y;
				cout << curX << ", " << curY << "\n";

				if (victimMoving == 0)
				{
					lastVictimX = curVictimX; lastVictimY = curVictimY;
					auto vMove = victimMover(curVictimX, curVictimY);
					curVictimX = vMove.first, curVictimY = vMove.second;
					victimMoving++;
				}
				else
					victimMoving++; victimMoving %= 5;

				if (curX == 2047 && curY == 2047)
					return { curX,curY };
			}
		}

		if (failure)
			break;
	}
	return { curX,curY };
}


bool inZone(char zone, int curX, int curY)
{
	double distance = sqrt((curVictimY - curY) * (curVictimY - curY) + (curVictimX - curX) * (curVictimX - curX));
	if (distance < 25)
	{
		if (zone == 'A')
			return true;
	}
	if (distance < 100)
	{
		if (zone == 'B')
			return true;
	}
	if (distance < 200)
	{
		if (zone == 'C')
			return true;
	}
	else
	{
		if (zone == 'D')
			return true;
	}
	return false;
}
*/

void getFollowing(int curX, int curY, int curVictimX, int curVictimY, int timesteps)
{
	int victimMoving = 0;
	int lastVictimX = curVictimX-1, lastVictimY = curVictimY; // because only going to the right


	//freopen("following_trajectories.csv", "w", stdout); // opens file to write to
	// allows use std output to write to the file

	
	//label dataset
	
	int t = 1;
	while (t<=timesteps)  //(make_pair(curX, curY) != make_pair(curVictimX, curVictimY))
	{
		// dynamic chasing
		
		if (victimMoving == 0)
		{
			lastVictimX = curVictimX; lastVictimY = curVictimY;
			auto vMove = victimMover(curVictimX, curVictimY);
			curVictimX = vMove.first, curVictimY = vMove.second;
			victimMoving++;
		}
		else
			victimMoving++; victimMoving %= victim_speed;

		if (!behind(curX, curY, curVictimX, curVictimY))
		{
			// get to behind

			// trying to loop around the victim, so chooses move that stays equidistant from victim
			
			vector<pair<int, int>> moveList;
			for (int i = -1; i < 1; i++) // NOTE: SINCE THIS SIM ONLY HAS RIGHT TRAVELLING BOAT V, LIMITED THE ROUNDABOUT
											// SO I DONT HAVE TO HAVE A GIANT IF STATEMENT, BUT IF BOAT V MOVEMENT CHANGES THEN IT IS NEEDED
			{
				for (int j = -1; j <= 1; j++)
				{
					if (!(i == 0 && j == 0))
					{
						moveList.push_back(make_pair(i, j));
						moveList.push_back(make_pair(i, j));
					}
				}
			}

			

			double curDist = sqrt((curVictimY - curY)*(curVictimY - curY) + (curVictimX - curX)*(curVictimX - curX));
			double minDistAway = 1000000; // away from the curDist
			pair<int, int> returnMove;
			for (auto i : moveList)
			{
				// calc distance after move
				// find one closest to cur distance
				double temp = sqrt((curVictimY - (curY + i.second))*(curVictimY - (curY + i.second))
					+ (curVictimX - (curX + i.first))*(curVictimX - (curX + i.first)));
				if (std::abs(curDist-temp) < minDistAway)
				{
					minDistAway = std::abs(curDist - temp);
					returnMove = i;
				}
			}

			//
			pair<int,int> p = returnMove;
			curX += p.first;
			curY += p.second;
			t++;
			cout << curX << ", " << curY << "," << curVictimX  << "," << curVictimY << "\n";
		}
		// move with three states
		else
		{
			pair<int, int> temp;
			// randomly choose one of three states: chasing/correction, randomwalk, and zig-zag
			int choice = rand() % 3 + 1;

			if (choice == 1 || choice == 2)
			{
				for (int i = 0; i < 15 + rand() % 10; i++)
				{
					
					if (choice == 1)
					{
						//chase/correction
						int r = rand() % 5;
						if (r == 0)
						{
							// random walk
							temp = randMove(curX, curY);
						}
						else
							temp = bresenhamstep({curX, curY}, {curVictimX, curVictimY}, 2)[1];
					}
					else if (choice == 2)
					{
						// random walk
						temp = randMove(curX, curY);
					}

					if (victimMoving == 0)
					{
						lastVictimX = curVictimX; lastVictimY = curVictimY;
						auto vMove = victimMover(curVictimX, curVictimY);
						curVictimX = vMove.first, curVictimY = vMove.second;
						victimMoving++;
					}
					else
						victimMoving++; victimMoving %= victim_speed;

					curX = temp.first; curY = temp.second;
					//write time and coords to a file
					cout << curX << ", " << curY << "," << curVictimX  << "," << curVictimY << "\n";
					t++;

					if (curX == 2047 && curY == 2047 || t >= timesteps)
						break;
				}
			}
			else if (choice == 3)
			{
				/////
				pair<int,int> temp;

				// zigzag
				int i = 15 + rand() % 10;

				// randomly choose a cardinal direction to zig zag in
				int direction = rand() % 4 + 1;
				pair<int, int> move1, move2, move3 = { 0,0 };
				if (direction == 1)
				{
					// north
					move1 = { -1,1 };
					move2 = { 1,1 };
				}
				if (direction == 2)
				{
					// south
					move1 = { -1,-1 };
					move2 = { 1,-1 };
				}
				if (direction == 3)
				{
					// east
					move1 = { 1,-1 };
					move2 = { 1,1 };
				}
				if (direction == 4)
				{
					// west
					move1 = { -1,-1 };
					move2 = { -1,1 };
				}

				int j = 0;
				bool failure = false;
				while (j < i && t<= timesteps)
				{
					
					int segmentLength = i / 5 + rand() % 3 - 1;
					j += segmentLength;
					if (j > i)
						segmentLength -= j - i;

					int randMoveType = rand() % 3 + 1;
					pair<int, int> curMove;
					if (randMoveType == 1)
						curMove = move1;
					else if (randMoveType == 2)
						curMove = move2;
					else if (randMoveType == 3)
						curMove = move3;

					for (int k = 0; k < segmentLength; k++)
					{
						int x = curX; int y = curY;

						x += curMove.first; y += curMove.second;

						if (x < 0 || x > 4096 || y < 0 || y > 4096)
						{
							failure = true;
							break;
						}
						else
						{
							curX = x; curY = y;
							cout << curX << ", " << curY << ',' << curVictimX << ',' << curVictimY << "\n";
							t++;
							if (victimMoving == 0)
							{
								lastVictimX = curVictimX; lastVictimY = curVictimY;
								auto vMove = victimMover(curVictimX, curVictimY);
								curVictimX = vMove.first, curVictimY = vMove.second;
								victimMoving++;
							}
							else
								victimMoving++; victimMoving %= victim_speed;

							if (curX == 2047 && curY == 2047 || t >= timesteps)
								temp = { curX,curY };
								break;
						}
					}


					if (failure)
						break;
				}
				temp = { curX,curY };







				/////
				curX = temp.first; curY = temp.second;
			}
		}

		//if (inZone('A', curX, curY))
		//	break;
		
	}
}


void doFollowing(int n, int timesteps, int buffersize, string filename)
{

	/*
	int n = 50; //number of trajectories
    
    int timesteps = 6000;
    int buffersize = 128; // used in entropybuffer calcs
	*/

	ofstream foltraj, entropyfile;
	bool isTraining = true;

	if (filename != "following_trajectories.csv"){
		isTraining = false;
	}
	foltraj.open(filename);
	if (isTraining) {
		entropyfile.open("entropies_fol.csv");
	}
	

	//freopen("following_trajectories.csv", "w", stdout); // opens file to write to std
	//  cout << "ux" << ", " << "uy" << "," <<"vx" << "," << "vy" << "\n";
    for (int k = 1; k<= n; k++){ //looping through each trajectory
        pair<int,int> chaser = {2048,2048}; //chaser starts in the middle
        std::pair<int,int> boatPositions[timesteps] = {};
        std::pair<int,int> followingBoatPositions[timesteps] = {};
		pair<int,int> runner = {2050+pow((-1),rand()%2)*(rand()%2000),2050+pow((-1),rand()%2)*(rand()%2000)};
		foltraj << k << "\n";
		int curX = chaser.first, curY = chaser.second, curVictimX = runner.first, curVictimY = runner.second;

		int victimMoving = 0;
		int lastVictimX = curVictimX-1, lastVictimY = curVictimY; // because only going to the right


		//freopen("following_trajectories.csv", "w", stdout); // opens file to write to
		// allows use std output to write to the file

		
		//label dataset
		
		int t = 0;
		while (t<=timesteps)  //(make_pair(curX, curY) != make_pair(curVictimX, curVictimY))
		{
			// dynamic chasing
			
			if (victimMoving == 0)
			{
				lastVictimX = curVictimX; lastVictimY = curVictimY;
				auto vMove = victimMover(curVictimX, curVictimY);
				curVictimX = vMove.first, curVictimY = vMove.second;
				victimMoving++;
			}
			else
				victimMoving++; victimMoving %= victim_speed;

			if (!behind(curX, curY, curVictimX, curVictimY))
			{
				// get to behind

				// trying to loop around the victim, so chooses move that stays equidistant from victim
				vector<pair<int, int>> moveList;
				for (int i = -1; i < 1; i++) // NOTE: SINCE THIS SIM ONLY HAS RIGHT TRAVELLING BOAT V, LIMITED THE ROUNDABOUT
												// SO I DONT HAVE TO HAVE A GIANT IF STATEMENT, BUT IF BOAT V MOVEMENT CHANGES THEN IT IS NEEDED
				{
					for (int j = -1; j <= 1; j++)
					{
						if (!(i == 0 && j == 0))
						{
							moveList.push_back(make_pair(i, j));
							moveList.push_back(make_pair(i, j));
						}
					}
				}

				double curDist = sqrt((curVictimY - curY)*(curVictimY - curY) + (curVictimX - curX)*(curVictimX - curX));
				double minDistAway = 1000000; // away from the curDist
				pair<int, int> returnMove;
				for (auto i : moveList)
				{
					// calc distance after move
					// find one closest to cur distance
					double temp = sqrt((curVictimY - (curY + i.second))*(curVictimY - (curY + i.second))
						+ (curVictimX - (curX + i.first))*(curVictimX - (curX + i.first)));
					if (std::abs(curDist-temp) < minDistAway)
					{
						minDistAway = std::abs(curDist - temp);
						returnMove = i;
					}
				}

				//
				pair<int,int> p = returnMove;
				curX += p.first;
				curY += p.second;
				followingBoatPositions[t] = {curX,curY};
				t++;
				//cout << curX << ", " << curY << "," << curVictimX  << "," << curVictimY << "\n";
			}
			// move with three states
			else
			{
				pair<int, int> temp;
				// randomly choose one of three states: chasing/correction, randomwalk, and zig-zag
				int choice = rand() % 3 + 1;

				if (choice == 1 || choice == 2)
				{
					for (int i = 0; i < 15 + rand() % 10; i++)
					{
						
						if (choice == 1)
						{
							//chase/correction
							int r = rand() % 5;
							if (r == 0)
							{
								// random walk
								temp = randMove(curX, curY);
							}
							else
								temp = bresenhamstep({curX, curY}, {curVictimX, curVictimY}, 2)[1];
						}
						else if (choice == 2)
						{
							// random walk
							temp = randMove(curX, curY);
						}

						if (victimMoving == 0)
						{
							lastVictimX = curVictimX; lastVictimY = curVictimY;
							auto vMove = victimMover(curVictimX, curVictimY);
							curVictimX = vMove.first, curVictimY = vMove.second;
							victimMoving++;
						}
						else
							victimMoving++; victimMoving %= victim_speed;

						curX = temp.first; curY = temp.second;
						//write time and coords to a file
						
						followingBoatPositions[t] = {curX,curY};
						//cout << curX << ", " << curY << "," << curVictimX  << "," << curVictimY << "\n";
						t++;

						if (curX == 2047 && curY == 2047 || t >= timesteps)
							break;
					}
				}
				else if (choice == 3)
				{
					/////
					pair<int,int> temp;

					// zigzag
					int i = 15 + rand() % 10;

					// randomly choose a cardinal direction to zig zag in
					int direction = rand() % 4 + 1;
					pair<int, int> move1, move2, move3 = { 0,0 };
					if (direction == 1)
					{
						// north
						move1 = { -1,1 };
						move2 = { 1,1 };
					}
					if (direction == 2)
					{
						// south
						move1 = { -1,-1 };
						move2 = { 1,-1 };
					}
					if (direction == 3)
					{
						// east
						move1 = { 1,-1 };
						move2 = { 1,1 };
					}
					if (direction == 4)
					{
						// west
						move1 = { -1,-1 };
						move2 = { -1,1 };
					}

					int j = 0;
					bool failure = false;
					while (j < i && t<= timesteps)
					{
						
						int segmentLength = i / 5 + rand() % 3 - 1;
						j += segmentLength;
						if (j > i)
							segmentLength -= j - i;

						int randMoveType = rand() % 3 + 1;
						pair<int, int> curMove;
						if (randMoveType == 1)
							curMove = move1;
						else if (randMoveType == 2)
							curMove = move2;
						else if (randMoveType == 3)
							curMove = move3;

						for (int k = 0; k < segmentLength; k++)
						{
							int x = curX; int y = curY;

							x += curMove.first; y += curMove.second;

							if (x < 0 || x > 4096 || y < 0 || y > 4096)
							{
								failure = true;
								break;
							}
							else
							{
								curX = x; curY = y;
								
								followingBoatPositions[t] = {curX,curY};
								//cout << curX << ", " << curY << ',' << curVictimX << ',' << curVictimY << "\n";
								t++;
								if (victimMoving == 0)
								{
									lastVictimX = curVictimX; lastVictimY = curVictimY;
									auto vMove = victimMover(curVictimX, curVictimY);
									curVictimX = vMove.first, curVictimY = vMove.second;
									victimMoving++;
								}
								else
									victimMoving++; victimMoving %= victim_speed;

								if (curX == 2047 && curY == 2047 || t >= timesteps)
									temp = { curX,curY };
									break;
							}
						}


						if (failure)
							break;
					}
					temp = { curX,curY };

					/////
					curX = temp.first; curY = temp.second;
				}
			}

			//if (inZone('A', curX, curY))
			//	break;
			
		}

		for (int z = 0; z <= timesteps; z++){
			foltraj << followingBoatPositions[z].first << ',' << followingBoatPositions[z].second << ',' << runner.first+int(z/victim_speed) << ',' << runner.second<< '\n';
		}


		if (isTraining){
			entropyfile << findEntropyBuffer(buffersize,timesteps,followingBoatPositions)<< '\n';
		}
	}

	if (isTraining){
		entropyfile.close();
	}
	foltraj.close();

}


