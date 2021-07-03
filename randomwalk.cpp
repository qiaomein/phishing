#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
#include<fstream>
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

int main() {

    //file
    std::ofstream myfile;
    myfile.open("randomwalk.csv");
    

    std::cout << "Enter starting coordinates then elapsed time." << std::endl;
    float tmax;
    int x, y;
    string current_zone;
    bool isInvis = false;
    std::cin >> x >> y >> tmax;

    srand(time(NULL));
    float dt = 1;

    myfile << std::to_string(x) + "," + std::to_string(y) + "\n";

    for (float i = 0; i <= tmax; i = i + dt){
        int rstate = rand() % 10;
        current_zone = zone(x,y);

        if (current_zone == "A") {
            std::cout << x << " " << y << "    " << current_zone << std::endl;
            break;
        }
        if (rstate == 0){
            isInvis = !isInvis;
        }

        if (rstate % 3 == 0 && rstate != 0){ // north is 3,6,9
            y++;
            if (rstate == 3){
                x--;
            }
            else if (rstate == 9){
                x++;
            }
        }
        else if (rstate % 3 == 1){ //south is 1,4,7
            y--;
            if (rstate == 1){
                x--;
            }
            else if (rstate == 7){
                x ++;
            }
        }
        else if (rstate == 2){ // dont change y 2,8 (5 is stay)
            x--;
        }
        else if (rstate == 8) {
            x ++;
        }

        if (x < 0){
        x = 0;
        }
        if (x > 4096){
            x = 4096;
        }
        if (y < 0){
            y = 0;
        }
        if (y > 4096){
            y = 4096;
        }

        myfile << std::to_string(x) + "," + std::to_string(y) + "\n";
        
        // std::cout << x << " " << y << "    " << current_zone << std::endl;

        // std::cout << x << " " << y << "    " << rstate << std::endl;
    }
    std::cout << x << " " << y << "    " << current_zone << std::endl;
    

    myfile.close();
    return 0;
}