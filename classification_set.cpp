#include "stdSysImports.h"
#include "bresenham.h"

using namespace std;

int main () {

    ofstream myfile;
    myfile.open("trajectories.csv");

    int n = 200; //number of trajectories
    
    

    int timesteps = 2000;    

    for (int k = 0; k< n; k++){ //looping through each trajectory
        pair<int,int> chaser = {2048,2048}; //chaser starts in the middle
        std::pair<int,int> boatPositions[timesteps] = {};

        boatPositions[0] = chaser;
        int dir = rand() % 4 + 1; 
        pair<int,int> runner = {(rand() % 2)*(chaser.first+512) + rand() % (chaser.first-512) + 1,(rand() % 2)*(chaser.second+512) +rand() % (chaser.second-512) + 1}; //randomize runner pos

        int traj = rand()%3;
        string activity;
        if (traj == 0) {activity = "random walk";}
        else if (traj == 1)
        {activity = "chasing";}
        else{
            activity = "following";
            }

        myfile<<activity<<',';


        for (int i = 1; i<= timesteps; i++){ //looping through each step
            int currX, currY;
            
            if (traj == 0){
                currX = boatPositions[i-1].first;
                currY = boatPositions[i-1].second;
                boatPositions[i] = randMove(currX, currY);
            }
            else if (traj == 1){
                currX = boatPositions[i-1].first;
                currY = boatPositions[i-1].second;
                if (currX != runner.first && currY != runner.second && currX != -1){ //checking for collision
                    boatPositions[i] = bresenhamstep(currX,currY,runner.first,runner.second);
                }
                else{
                    boatPositions[i] = {-1,-1};
                }
            }
            
            else{
                currX = boatPositions[i-1].first;
                currY = boatPositions[i-1].second;
                if (currX != runner.first && currY != runner.second && currX != -1){
                    boatPositions[i] = randFollowMove(currX,currY,runner.first,runner.second);
                }
                else{
                    boatPositions[i] = {-1,-1};
                }
            }

            
            myfile << currX << "," << currY << ",";
            
            //move runner
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
        myfile<<'\n';
    }

    myfile.close();

    return 0;
}