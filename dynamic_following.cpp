#include "stdSysImports.h"
#include "bresenham.h"

using std::string;

int main (){
    std::ofstream myfile;
	myfile.open("dynamic_following.csv");
	// v is chasing u
	std::pair<int,int> u = {1000,200};
	std::pair<int,int> v = {500,2000};

	//179, 279, ,158, 321

	int tmax = 10000;
	
	for (int t = 0; t <= tmax; t++){
		
		
		v = randFollowMove(v.first,v.second,u.first,u.second);
		

		if (u==v){
			break;
		}

		myfile << std::to_string(u.first) + ", " + std::to_string(u.second) + ", ," << std::to_string(v.first) + ", " + std::to_string(v.second) + "\n";
		if (t % 16 >11){
			
			u.first++;
			u.second = u.second + 2;
		}
	}

	myfile.close();




    return 0;
}