#include "stdSysImports.h"
#include "bresenham.h"

using std::vector;
using std::string;
using std::pair;


float slope(int x1, int y1, int x2, int y2){
    return float((y2-y1))/(x2-x1);
}

void bresenham1(int x1, int y1, int x2, int y2, string filename) // for slopes <= 1
{
    std::ofstream myfile;

    myfile.open(filename);

    int o45 = 0, o8 = 0;

    if (x2-x1<0 && y2-y1>0) {
        x2 += 2*(x1-x2);
        o45 = 1;
        
    }
    else if (x2 - x1 < 0 && y2-y1 < 0){
       x2 += 2*(x1-x2); 
       y2 += 2*(y1-y2);
       o45 = 1;
       o8 = 1;
    }
    else if (x2 - x1 > 0 && y2 - y1 < 0){
       y2 += 2*(y1-y2);
       o8 = 1;
    }

   int m_new = 2 * (y2 - y1);
   int slope_error_new = m_new - (x2 - x1);
   for (int x = x1, y = y1; x <= x2; x++)
   {
      //std::cout << "(" << x - o45*(2*(x-x1)) << "," << y - o8*(2*(y-y1)) << ")\n";
      myfile << std::to_string(x - o45*(2*(x-x1))) + ", " + std::to_string(y - o8*(2*(y-y1))) + "\n";


      // Add slope to increment angle formed
      slope_error_new += m_new;
 
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0)
      {
         y++;
         slope_error_new  -= 2 * (x2 - x1);
      }
   }
   myfile.close();
}

void bresenham2(int x1, int y1, int x2, int y2, string filename) //for reflected slopes of > 1
{
    std::ofstream myfile;

    myfile.open(filename);

   int o36 = 0, o7 = 0;

    if (x2-x1<0 && y2-y1>0) {
        x2 += 2*(x1-x2);
        o36 = 1;
    }
    else if (x2 - x1 < 0 && y2-y1 < 0){
       x2 += 2*(x1-x2); 
       y2 += 2*(y1-y2);
       o36 = 1;
       o7 = 1;
    }
    else if (x2 - x1 > 0 && y2 - y1 < 0){
       y2 += 2*(y1-y2);
       o7 = 1;
    }


   int m_new = 2 * (x2 - x1);
   int slope_error_new = m_new - (y2 - y1);
   for (int x = x1, y = y1; y <= y2; y++)
   {
      //std::cout << "(" << x - o36*(2*(x-x1)) << "," << y - o7*(2*(y-y1)) << ")\n";
      myfile << std::to_string(x - o36*(2*(x-x1))) + ", " + std::to_string(y - o7*(2*(y-y1))) + "\n";

      // Add slope to increment angle formed
      slope_error_new += m_new;
 
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0)
      {
         x++;
         slope_error_new  -= 2 * (y2 - y1);
      }
   }
   myfile.close();
}

void bresenham(int x1, int y1, int x2, int y2, string filename){
   float m = slope(x1,y1,x2,y2);
   
   if (abs(m)<= 1) {
      bresenham1(x1,y1,x2,y2,filename);
   }
   else{
      bresenham2(x1,y1,x2,y2,filename);
   }
}

vector<pair<int,int>> bresenham1step(int x1, int y1, int x2, int y2, int steps) // for slopes <= 1
{

    int o45 = 0, o8 = 0;

    if (x2-x1<0 && y2-y1>0) {
        x2 += 2*(x1-x2);
        o45 = 1;
        
    }
    else if (x2 - x1 < 0 && y2-y1 < 0){
       x2 += 2*(x1-x2); 
       y2 += 2*(y1-y2);
       o45 = 1;
       o8 = 1;
    }
    else if (x2 - x1 > 0 && y2 - y1 < 0){
       y2 += 2*(y1-y2);
       o8 = 1;
    }

   vector<pair<int,int>> temp(steps);

   int m_new = 2 * (y2 - y1);
   int slope_error_new = m_new - (x2 - x1);
   for (int x = x1, y = y1, i = 0; x <= x2 && i < 1+steps; x++, i++)
   {
      temp[i] = {x - o45*(2*(x-x1)),y - o8*(2*(y-y1))};

      // Add slope to increment angle formed
      slope_error_new += m_new;
 
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0)
      {
         y++;
         slope_error_new  -= 2 * (x2 - x1);
      }
      
   }
   return temp;
}

vector<pair<int,int>> bresenham2step(int x1, int y1, int x2, int y2, int steps) //for reflected slopes of > 1
{
   int o36 = 0, o7 = 0;

    if (x2-x1<0 && y2-y1>0) {
        x2 += 2*(x1-x2);
        o36 = 1;
    }
    else if (x2 - x1 < 0 && y2-y1 < 0){
       x2 += 2*(x1-x2); 
       y2 += 2*(y1-y2);
       o36 = 1;
       o7 = 1;
    }
    else if (x2 - x1 > 0 && y2 - y1 < 0){
       y2 += 2*(y1-y2);
       o7 = 1;
    }

   vector<pair<int,int>> temp(steps);

   int m_new = 2 * (x2 - x1);
   int slope_error_new = m_new - (y2 - y1);
   for (int x = x1, y = y1, i = 0; y <= y2 && i < 1+ steps; y++, i ++)
   {

      temp[i] = std::make_pair(x - o36*(2*(x-x1)), y - o7*(2*(y-y1)));
      //std::cout << "(" << x - o36*(2*(x-x1)) << "," << y - o7*(2*(y-y1)) << ")\n";
      //myfile << std::to_string(x - o36*(2*(x-x1))) + ", " + std::to_string(y - o7*(2*(y-y1))) + "\n";
      
      // Add slope to increment angle formed
      slope_error_new += m_new;
 
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0)
      {
         x++;
         slope_error_new  -= 2 * (y2 - y1);
      }
      
      
   }
   return temp;
}

vector<pair<int,int>> bresenhamstep(std::pair<int,int> u, std::pair<int,int> v,int steps){
   int x1 = u.first, x2 = v.first, y1 = u.second, y2 = v.second;
   vector<pair<int,int>> edgecase(steps);
   if (x1==x2){
      int dir = (y2-y1)/abs(y2-y1);
      for (int i = 0;i < steps;i++){
         edgecase[i] = std::make_pair(x1,y1 + i*dir);
      }
      return edgecase;
   }
   else if (y1 == y2){
      int dir = (x2-x1)/abs(x2-x1);
      for (int i = 0;i < steps;i++){
         edgecase[i] = std::make_pair(x1+i*dir,y1);
      }
      return edgecase;
   }
   else{
   float m = slope(x1,y1,x2,y2);
   
   if (abs(m)<= 1) {
      return bresenham1step(x1,y1,x2,y2,steps);
   }
   else{
      return bresenham2step(x1,y1,x2,y2,steps);
   }
   }
}



/*
int main () {
    //file
    //std::ofstream myfile;
    //myfile.open("bresenhamstep.csv");

    int x0, y0, x1, x2, y1, y2;
    vector<std::pair<int,int>> boat(600);
    std:: cout << boat.size() << std::endl;

    

    //std::cout << "Enter x2, y2:" << std::endl;
    //std::cin >> x2 >> y2;
    x2 = 2048; y2 = 2048;
    boat = bresenhamstep({2500,3000},{x2,y2},1000);

   for (int i = 0;i<1000;i++){

      std::cout << i << "   " << boat[i].first<< ' ' << boat[i].second << std::endl;

      
      
      
   }
   //myfile.close();
   
   return 0;
}

*/


