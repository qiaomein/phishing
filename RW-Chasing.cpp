#include "stdSysImports.h"
#include "bresenham.h"

using std::string;


/*
############# README ###########
analyzing and simulating u is chasing a randomwalking v
(not using this for training but seeing how well the model can classify dynamic trajectories)
*/
int main() {
    std::ofstream myfile;
    myfile.open("RW-Chasing.csv");
    int trajectories, timesteps, buffersize;

    trajectories = 500; 
    timesteps = 2000;
    buffersize = 128;

    for (int k = 1; k <= trajectories ; k ++){ // looping over each trajectory
        std::pair<int,int> uPositions[timesteps] = {};
        std::pair<int,int> vPositions[timesteps] = {};

        // start chaser in the center and randomly set v outside 512 units from center
        std::pair<int,int> u0 = {2048,2048};
        std::pair<int,int> v0 = {(rand() % 2)*(u0.first+512) + rand() % (u0.first-512) + 1,(rand() % 2)*(u0.second+512) +rand() % (u0.second-512) + 1}; //randomize runner pos
        uPositions[0] = u0;
        vPositions[0] = v0;
        myfile << k << '\n';

        for (int i = 1; i <= timesteps; i++){ // loop through each time step
            vPositions[i] = randMove(vPositions[i-1].first,vPositions[i-1].second);
            uPositions[i] = bresenhamstep(uPositions[i-1].first,uPositions[i-1].second,vPositions[i-1].first,vPositions[i-1].second);



            myfile << uPositions[i-1].first << "," << uPositions[i-1].second << "," << vPositions[i-1].first << "," << vPositions[i-1].second << "\n";
        }
    }


    return 0;

}