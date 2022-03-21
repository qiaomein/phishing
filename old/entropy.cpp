#include "stdSysImports.h"
#include "bresenham.h"

using std::string;

int main() {

    std::ofstream myfile;

    myfile.open("output.csv");

    int timesteps = 5000;
    int buffersize = 100;

    std::pair <int,int> startboatpos = { 4096/2, 4096/2};
    std::pair<int,int> boatPositions[timesteps] = {};
    std::pair<int,int> followingBoatPositions[timesteps] = {};
    std::pair<int,int> chasingBoatPositions[timesteps] = {};

    boatPositions[0] = startboatpos;
    chasingBoatPositions[0] = startboatpos;
    followingBoatPositions[0] = startboatpos;

    // dynamic chasing
    std::pair<int,int> poorsod = {0,0};
    

    for (int i = 1; i<= timesteps; i++){
        
        int currXf = followingBoatPositions[i-1].first;
        int currYf = followingBoatPositions[i-1].second;
        int currXc = chasingBoatPositions[i-1].first;
        int currYc = chasingBoatPositions[i-1].second;
        int currX = boatPositions[i-1].first;
        int currY = boatPositions[i-1].second;
        boatPositions[i] = randMove(currX, currY);
        chasingBoatPositions[i] = bresenhamstep(currXc,currYc,poorsod.first,poorsod.second);
        followingBoatPositions[i] = randFollowMove(currXf,currYf,poorsod.first,poorsod.second);
        myfile << currX << "," << currY << "," << "," << currXc << "," << currYc << "," << "," << currXf << "," << currYf << ", " <<poorsod.first << "," << poorsod.second << "\n";
        // moving the poor sod ;(
            /*
        if (i % 10 > 3){
            poorsod.first++;
        }
        */
    }

    /*
    for (int i = 0; i <= timesteps; i++){
        std::cout << boatpositions[i].first <<',' <<boatpositions[i].second << std::endl;
    }
    */
    std::cout << "entropy of randomwalk \n" << findEntropy(timesteps, boatPositions) << std::endl;
    std::cout << "entropy of chasing \n" << findEntropy(timesteps, chasingBoatPositions) << std::endl;    
    std::cout << "entropy of following \n" << findEntropy(timesteps, followingBoatPositions) << std::endl; 

    myfile.close();
    std::cout << "avg: " << findEntropyBuffer(buffersize,timesteps,boatPositions) << ", "
    << findEntropyBuffer(buffersize,timesteps,chasingBoatPositions) << ", "<< findEntropyBuffer(buffersize,timesteps,followingBoatPositions) << std::endl;
    return 0;
}