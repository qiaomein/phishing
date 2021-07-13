#include "stdSysImports.h"
#include "bresenham.h"

using std::string;

int main(){
	
	//initial conditions
	int chaseX = 100, chaseY = 20, staticX = 99, staticY = -300;


	string filename = "stationary_chasing.csv";
	bresenham(chaseX,chaseY,staticX,staticY,filename);
	
	return 0;
}