#include "stdSysImports.h"
#include "bresenham.h"

using std::string;

int main() {
    int timesteps = 1000;

    std::pair <int,int> startboatpos = { 4096/2, 4096/2};
    std::pair<int,int> boatpositions[timesteps] = {};
    
    std::pair<int,int> chasingBoatPositions[timesteps] = {};
    boatpositions[0] = startboatpos;
    chasingBoatPositions[0] = startboatpos;

    for (int i = 1; i<= timesteps; i++){
        int currXc = chasingBoatPositions[i-1].first;
        int currYc = chasingBoatPositions[i-1].second;
        int currX = boatpositions[i-1].first;
        int currY = boatpositions[i-1].second;
        boatpositions[i] = randMove(currX, currY);
        chasingBoatPositions[i] = bresenhamstep(currXc,currYc,startboatpos.first-300,startboatpos.second-200);
    }

    /*
    for (int i = 0; i <= timesteps; i++){
        std::cout << boatpositions[i].first <<',' <<boatpositions[i].second << std::endl;
    }
    */
    std::cout << "entropy of randomwalk \n" << findEntropy(timesteps, boatpositions) << std::endl;
    std::cout << "entropy of chasing \n" << findEntropy(timesteps, chasingBoatPositions) << std::endl;    

    return 0;
}