#include "stdSysImports.h"
using std::string;

string zone(int x, int y) {
    if (x>1792 && y >1792 && x<2304 && y > 1792 && x<2304 && y<2304 && x>1792 && y<2304){
        return "A";
    }
    else if (x>1536 && y >1536 && x<2560 && y > 1536 && x<2560 && y<2560 && x>1536 && y<2560){
        return "B";
    }
    else if (x>1024 && y >1024 && x<3072 && y > 1024 && x<3072 && y<3072 && x>1024 && y<3072){
        return "C";
    }
    else{
        return "D";
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
	if (gen == 3){
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
		return { -1,-1 };
	else
		return { x,y };
}


float findEntropy (int timesteps, std::pair<int,int> boatpositions[]) {
	int dx,dy;
	int p[9]; //0-8 each index represents a move (not accounting for invis yet)
    for (int i = 0; i <= timesteps; i ++){
		dx = boatpositions[i].first - boatpositions[i-1].first;
		dy = boatpositions[i].second - boatpositions[i-1].second;
		if (dx == 1){
			if (dy == 1){
				p[2] ++;
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
		else{
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
    }
	float H = 0; float P;
	for (int j = 0; j <= 8; j++){
		P = p[j]/float(9);
		H += P*log2(P);
	}
	return H;

}