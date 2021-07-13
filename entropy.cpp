#include "stdSysImports.h"
#include "bresenham.h"

using std::string;

int main() {
    int timesteps = 100;

    std::pair <int,int> startboatpos = { 4096/2, 4096/2};
    std::pair<int,int> boatpositions[timesteps] = {};
    boatpositions[0] = startboatpos;

    for (int i = 1; i<= timesteps; i++){
        int currX = boatpositions[i-1].first;
        int currY = boatpositions[i-1].second;
        boatpositions[i] = randMove(currX, currY);
    }

    /*
    for (int i = 0; i <= timesteps; i++){
        std::cout << boatpositions[i].first <<',' <<boatpositions[i].second << std::endl;
    }
    */
    std::cout << findEntropy(timesteps, boatpositions) << std::endl;    

    return 0;
}