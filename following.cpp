#include "stdSysImports.h"
#include "bresenham.h"

using namespace std;


bool invis = false;

pair<int, int> randFollowMove(int curX, int curY, int goalX, int goalY) //based on probability matrix
{
	// 30% chance do bresenham
	// 5% for each of invis or 3 directions away
	// everything else 10%
	pair<int, int> t = bresenhamstep(curX, curY, goalX, goalY);
	pair<int, int> chaseMove = { t.first - curX, t.second - curY };
	//chaseMove = fixBresenham(chaseMove);
	
	// set up randomizer list
	map<pair<int, int>,bool> found;
	vector<pair<int, int>> randomizedList;
	randomizedList.push_back(chaseMove);
	randomizedList.push_back({ -1 * chaseMove.first, -1 * chaseMove.second }); // 5%
	found[chaseMove] = true; found[{ -1 * chaseMove.first, -1 * chaseMove.second }] = true;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			int totalDiff = abs(chaseMove.first - i) + abs(chaseMove.second - j);
			if (totalDiff == 3) // if chase was north, this would be SW/SE
			{
				randomizedList.push_back({ i,j });
				found[{i, j}] = true;
			}
		}
	
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (!found[{i, j}])
			{
				randomizedList.push_back({ i,j });
			}
		}
	

	pair<int, int> randMove = { curX, curY };


	// note: commented directions are assuming bresenham outputs (0,1) as move
	// randomizing
	int moveNum = rand() % 20 + 1;
	if (moveNum > 0 && moveNum <= 6)
	{
		// go with chase
		randMove = { curX + chaseMove.first, curY + chaseMove.second };
	}
	else if (moveNum == 7)
	{
		// invis
		invis = true;
	}
	else if (moveNum == 8)
	{
		// south
		randMove = { curX + randomizedList[1].first, curY + randomizedList[1].second };
	}
	else if (moveNum == 9)
	{
		// south west
		randMove = { curX + randomizedList[2].first, curY + randomizedList[2].second };
	}
	else if (moveNum == 10)
	{
		// south east * 9 and 10 may be swapped
		randMove = { curX + randomizedList[3].first, curY + randomizedList[3].second };
	}

	else if (moveNum > 10 && moveNum <= 12) // from here on out is all 10%
		randMove = { curX + randomizedList[4].first, curY + randomizedList[4].second };
	else if (moveNum > 12 && moveNum <= 14)
		randMove = { curX + randomizedList[5].first, curY + randomizedList[5].second };
	else if (moveNum > 14 && moveNum <= 16)
		randMove = { curX + randomizedList[6].first, curY + randomizedList[6].second };
	else if (moveNum > 16 && moveNum <= 18)
		randMove = { curX + randomizedList[7].first, curY + randomizedList[7].second };
	else if (moveNum > 18 && moveNum <= 20)
		randMove = { curX + randomizedList[8].first, curY + randomizedList[8].second };
	

	return randMove;
}


/*
int main(void)
{
	freopen("out.csv", "w", stdout); // opens file to write to
	// allows us to use std output to write to the file

	int curX = 1790, curY = 1790; // note: x is positive towards right, y is positive downwards

	for (int time = 0; time < 5000; time++)
	{
		//randomly move
		pair<int, int> temp = randFollowMove(curX, curY, 2047, 2047);
		curX = temp.first; curY = temp.second;

		//write time and coords to a file
		cout << curX << ", " << curY << "\n";
		
		///
		if (invis)
		{
			cout << "   invisible";
			invis = false;
		}
		cout << endl;
		////////

		if (time == 5000 || (curX == 2047 && curY == 2047)) // or some other condition
			break;

		//std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for one second (commented out for speed's sake)
		if (time % 500 == 0)
		{
			int fivehundred = true;
		}
	}
	return 0;
}
*/