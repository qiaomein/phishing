#include "stdSysImports.h"
#include "bresenham.h"

using std::string;



int main(){
	std::ofstream myfile;
	myfile.open("dynamic_chasing.csv");
	// v is chasing u
	std::pair<int,int> u = {1000,-200};
	std::pair<int,int> v = {500,100};

	//179, 279, ,158, 321

	int tmax = 1000;
	
	for (int t = 0; t <= tmax; t++){
		
		
		v = bresenhamstep(v.first,v.second,u.first,u.second);
		
		if (u==v){
			break;
		}

		myfile << std::to_string(u.first) + ", " + std::to_string(u.second) + ", ," << std::to_string(v.first) + ", " + std::to_string(v.second) + "\n";
		u.first--;
	}

	myfile.close();
	return 0;
}
