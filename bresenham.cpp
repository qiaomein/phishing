#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
#include<fstream>
using std::string;

float slope(int x1, int y1, int x2, int y2){
    return float((y2-y1))/(x2-x1);
}

int main () {
    //file
    std::ofstream myfile;

    myfile.open("bresenham.csv");

    int x0, y0, x1, x2, y1, y2;

    x1 = 0; y1 = 0;

    std::cout << "Enter x2, y2:" << std::endl;
    std::cin >> x2 >> y2;
    float m = slope(x1,y1,x2,y2);
    x0 = x1;
    y0 = y1;

    //set chasing boat as the origin
    x2 = x2-x1;
    y2 = y2-y1;
    x1 = 0;
    y1 = 0;
    
    std::cout<<x1<<y1<<x2<<y2<<std::endl;

    int q2 =1; int q3=1; int q4 =1;

    

    //control flow for other quadrants
    if (x2 < 0 && y2 >0){ // in q2
        x2 *= -1;
        q2 = -1;
    }
    else if (x2<0 && y2 < 0){
        x2*=-1; y2 *=-1;
        q3 = -1;
    }
    else if (x2>0 && y2 <0) {
        y2*=-1;
        q4 = -1;
    }
    std::cout << m << std::endl;
    if (abs(m) > 1) { //swap x and y if slope > 1
        std::cout << "m > 1" << std::endl;
        auto x1temp = x1;
        x1 = y1; y1 = x1temp;
        auto x2temp = x2;
        x2 = y2; y2 = x2temp;
        auto x0temp = x0; x0 = y0; y0 = x0temp;
    }


//bresenham scheme
    int m_new = 2 * (y2 - y1);
    int slope_error_new = m_new - (x2 - x1);
    //bresneham loop
    for (int x = x1, y = y1; x <= x2; x++)
    {
        

        //control flow for m > 1 and m <= 1
        if (abs(m)<= 1) {
        std::cout << "(" << q2*q3*(x+x0) << "," << q3*q4*(y+y0) << ")" << std::endl;
        myfile << std::to_string(q2*q3*(x+x0)) + "," +std::to_string(q3*q4*(y+y0)) + "\n";
        }
        else {
            std::cout << "(" << (q2*q3*(y+y0)) << "," << q3*q4*(x+x0) << ")" << std::endl;
        myfile << std::to_string(q2*q3*(y+y0)) + "," +std::to_string(q4*q3*(x+x0)) + "\n";
        }

        slope_error_new += m_new;

        if (slope_error_new >= 0)
        {
            y++;
            slope_error_new  -= 2 * (x2 - x1);
        }
    }

    
    


    myfile.close();
    return 0;
}