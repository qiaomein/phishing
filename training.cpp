#include "stdSysImports.h"
#include "bresenham.h"

using namespace std;



pair<int, int> randFollowMove(int curX, int curY, int goalX, int goalY) //based on probability matrix
{
    bool invis = false;
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
			int totalDiff = std::abs(chaseMove.first - i) + std::abs(chaseMove.second - j);
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


int main () {

    ofstream myfile; ofstream entropyfile;


    myfile.open("positions.csv");
    entropyfile.open("entropies.csv");

    int n = 50; //number of trajectories
    
    

    int timesteps = 2000;
    int buffersize = 128; // used in entropybuffer calcs

    

    for (int k = 1; k<= n; k++){ //looping through each trajectory
        pair<int,int> chaser = {2048,2048}; //chaser starts in the middle
        std::pair<int,int> boatPositions[timesteps] = {};
        std::pair<int,int> followingBoatPositions[timesteps] = {};
        std::pair<int,int> chasingBoatPositions[timesteps] = {};
        std::pair<int,int> threeFollowBoatPositions[timesteps] = {};

        boatPositions[0] = chaser;
        chasingBoatPositions[0] = chaser;
        followingBoatPositions[0] = chaser;
        threeFollowBoatPositions[0] = chaser;
        int dir = 1; //rand() % 4 + 1; 
        pair<int,int> runner = {(rand() % 2)*(chaser.first+512) + rand() % (chaser.first-512) + 1,(rand() % 2)*(chaser.second+512) +rand() % (chaser.second-512) + 1}; //randomize runner pos
        myfile << k << "\n";

        //declaring all vars for zigzag
        int choice, direction, segmentLength;
        pair<int, int> move1, move2, move3, curMove = { 0,0 };
        int randMoveType = rand() % 3 + 1;
        int m = 0;
        int zzl = 15 + rand() % 10;
        
        //getFollowing(chaser.first,chaser.second,timesteps);



        for (int i = 1; i<= timesteps; i++){ //looping through each time step

            //zigzag block update2
            if (i % zzl == 1) {
                

                choice = rand() % 3 + 1; //choose new state every zzl time steps

                direction = rand() % 4 + 1; //pick cardinal direction to zigzag in
                
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
                segmentLength = zzl/5 + rand() % 3;
                
            }



            int currX3f = threeFollowBoatPositions[i-1].first;
            int currY3f = threeFollowBoatPositions[i-1].second;

            int currXf = followingBoatPositions[i-1].first;
            int currYf = followingBoatPositions[i-1].second;
            int currXc = chasingBoatPositions[i-1].first;
            int currYc = chasingBoatPositions[i-1].second;
            int currX = boatPositions[i-1].first;
            int currY = boatPositions[i-1].second;

            //movement
            boatPositions[i] = randMove(currX, currY);
            
            if ((currXc != runner.first || currYc != runner.second) && currXc != -1){ //checking for collision
                chasingBoatPositions[i] = bresenhamstep(currXc,currYc,runner.first,runner.second);
            }
            else{
                chasingBoatPositions[i] = {-1,-1};
            }
//follow move
            if ((currXf != runner.first || currYf != runner.second) && currXf != -1){
                followingBoatPositions[i] = randFollowMove(currXf,currYf,runner.first,runner.second);
            }
            else{
                followingBoatPositions[i] = {-1,-1};
            }

            if (make_pair(currX3f,currY3f) != runner && currXf != -1 ) {
                
            
 
// control flow for 3state following
            
                if (choice == 1) //chasing
                {
                    threeFollowBoatPositions[i] = bresenhamstep(currX3f, currY3f, runner.first,runner.second);
                }
                else if (choice == 2)
                {
                    // random walk
                    threeFollowBoatPositions[i] = randMove(currX3f, currY3f);
                }              
                
                else //zigzag
                {   

                    if (m>segmentLength){ // if we are done with a zig prepare for zag
                        m = -1;
                        randMoveType ++;
                        }                  
                    
                    if (randMoveType % 2 == 0){
                        curMove = move1;
                    }
                    else if (randMoveType % 2 == 1){
                        curMove = move2;
                    }
                    else {
                        curMove = move3;
                    }
                    
                    m++;
                    
                    threeFollowBoatPositions[i] = {currX3f+curMove.first,currY3f+curMove.second};
                }
                
            }
            else {
                threeFollowBoatPositions[i] = {-1,-1};
            }

            myfile << currX << "," << currY << "," << currXc << "," << currYc 
            << "," << currXf << "," << currYf << "," << runner.first << "," << runner.second << "\n"; //<< "," << currX3f << "," << currY3f <<  "\n";
            if (i % 2 == 1){
                if (dir == 1){
                    runner.first++;
                }
                else if (dir == 2) {
                    runner.first --;
                }
                else if (dir == 3) {
                    runner.second ++;
                }
                else{
                    runner.second--;
                }
            }

        }

        // add following to positions
        string line;
        ifstream followingfile ("following_trajectories.csv");
        if (followingfile.is_open()){
            while (followingfile.good()){
                getline(followingfile,line);
                //cout << line << endl;
            }
            followingfile.close();
        }


    entropyfile << findEntropyBuffer(buffersize,timesteps,boatPositions) << ", "
    << findEntropyBuffer(buffersize,timesteps,chasingBoatPositions) << ", "
    << findEntropyBuffer(buffersize,timesteps,threeFollowBoatPositions) << "\n";

    }

    myfile.close(); entropyfile.close();

    return 0;
}
