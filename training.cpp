#include "stdSysImports.h"
#include "bresenham.h"

using namespace std;

int main () {

    ofstream myfile; ofstream entropyfile;
    myfile.open("positions.csv");
    entropyfile.open("entropies.csv");

    int n = 200; //number of trajectories
    
    

    int timesteps = 2000;
    int buffersize = 128;

    

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
        int dir = rand() % 4 + 1; 
        pair<int,int> runner = {(rand() % 2)*(chaser.first+512) + rand() % (chaser.first-512) + 1,(rand() % 2)*(chaser.second+512) +rand() % (chaser.second-512) + 1}; //randomize runner pos
        myfile << k << "\n";

        //declaring all vars for zigzag
        int choice, direction, segmentLength;
        pair<int, int> move1, move2, move3, curMove = { 0,0 };
        int randMoveType = rand() % 3 + 1;
        int m = 0;
        int zzl = 15 + rand() % 10;

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
                        randMoveType = rand() % 3 + 1;
                        }                  
                    
                    if (randMoveType == 1){
                        curMove = move1;
                    }
                    else if (randMoveType == 2){
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
            << "," << currXf << "," << currYf << "," <<runner.first << "," << runner.second << "," << currX3f << "," << currY3f <<  "\n";
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
    entropyfile << findEntropyBuffer(buffersize,timesteps,boatPositions) << ", "
    << findEntropyBuffer(buffersize,timesteps,chasingBoatPositions) << ", "
    << findEntropyBuffer(buffersize,timesteps,followingBoatPositions) << "\n";

    }

    myfile.close(); entropyfile.close();

    return 0;
}
