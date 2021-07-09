#include "stdSysImports.h"
#include "bresenham.h"

using std::string;


std::pair <int,int> moveSouth(int x, int y) {
	if (y-1 < 0){
		y = 0;
	}
	else{
		y--;
	}
	return {x,y};
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



int main(){
	

	int chaseX = 100, chaseY = 20, staticX = 1000, staticY = 500;
	string filename = "stationary_chasing.csv";
	bresenham(chaseX,chaseY,staticX,staticY,filename);
	
	return 0;
}