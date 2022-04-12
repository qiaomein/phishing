#include "stdSysImports.h"
#include "bresenham.h"

using namespace std;



int main () {

    ofstream myfile;
    myfile.open("trajectories.csv");

    int n = 200; //number of trajectories
    
    srand(time(0));

    

    int timesteps = 3000;    
    int chase_length = 20;
    int buffersize = pow(2,7); // used in entropybuffer calcs

    doFollowing(n,timesteps,buffersize,"trajectories_following.csv");

    for (int k = 1; k<= n; k++){ //looping through each trajectory


        pair<int,int> chaser = {2048,2048}; //chaser starts in the middle
        std::pair<int,int> randBoatPositions[timesteps] = {};
        pair<int,int> chaseBoatPositions[timesteps] = {};

        randBoatPositions[0] = chaser;
        chaseBoatPositions[0] = chaser;

        int dir = 1; 
        int runner_range = 512;
        pair<int,int> runner = {(rand() % 2)*(chaser.first+runner_range) + rand() % (chaser.first-runner_range) + 1,(rand() % 2)*(chaser.second+runner_range) +rand() % (chaser.second-runner_range) + 1}; //randomize runner pos
        
        //pair<int,int> runner = {(rand() % 2)*(chaser.first+512) + rand() % (chaser.first-512) + 1,(rand() % 2)*(chaser.second+512) +rand() % (chaser.second-512) + 1}; //randomize runner pos


        int victimSpeed = rand()%3 + 3;
        
        vector<pair<int,int>> curchase(10);
        int currXr, currYr, currXc, currYc;

        myfile << k << '\n';

        for (int i = 1; i<= timesteps; i++){ //looping through each step
            
            


            currXr = randBoatPositions[i-1].first;
            currYr = randBoatPositions[i-1].second;
            currXc = chaseBoatPositions[i-1].first;
            currYc = chaseBoatPositions[i-1].second;
            

            randBoatPositions[i] = randMove(currXr, currYr);


            if (currXc != runner.first && currYc != runner.second && currXc != -1){ //checking for collision
                if (i % chase_length == 1){ // update oldrunner every chase_length steps
                //cout<< 's' << endl;
                    curchase = bresenhamstep(make_pair(currXc,currYc),runner,chase_length); 
                }
                //std::cout << currXc << ' ' << currYc << "   " << runner.first << ' ' << runner.second << "   "<< curchase[i % chase_length].first << ' ' << curchase[i % chase_length].second << std::endl;
                
                else if (i % chase_length == 0){
                    chaseBoatPositions[i] = {currXc,currYc};
                }
                else
                {
                    chaseBoatPositions[i] = curchase[i % chase_length];
                }
            }
            else{
                chaseBoatPositions[i] = {-1,-1};
            }
        
            

            
            myfile << currXr << "," << currYr << "," << currXc << "," << currYc  << "," << runner.first << "," << runner.second << "\n";
            
            //move runner
            if (i % victimSpeed == 1){
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
    }

    myfile.close();

    return 0;
}