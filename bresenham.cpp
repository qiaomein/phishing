#include "stdSysImports.h"
#include "bresenham.h"

using std::string;



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


std::pair<int,int> bresenham1step(int x1, int y1, int x2, int y2) // for slopes <= 1
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

   std::pair<int,int> temp = {x1,y1};

   int m_new = 2 * (y2 - y1);
   int slope_error_new = m_new - (x2 - x1);
   for (int x = x1, y = y1, i = 0; x <= x2 && i < 2; x++, i++)
   {
      //std::cout << "(" << x - o45*(2*(x-x1)) << "," << y - o8*(2*(y-y1)) << ")\n";
      //myfile << std::to_string(x - o45*(2*(x-x1))) + ", " + std::to_string(y - o8*(2*(y-y1))) + "\n";
      temp = {x - o45*(2*(x-x1)),y - o8*(2*(y-y1))};

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

std::pair<int,int> bresenham2step(int x1, int y1, int x2, int y2) //for reflected slopes of > 1
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

   std::pair<int,int> temp = {x1,y1};

   int m_new = 2 * (x2 - x1);
   int slope_error_new = m_new - (y2 - y1);
   for (int x = x1, y = y1, i = 0; y <= y2 && i < 2; y++, i ++)
   {
      //std::cout << "(" << x - o36*(2*(x-x1)) << "," << y - o7*(2*(y-y1)) << ")\n";
      //myfile << std::to_string(x - o36*(2*(x-x1))) + ", " + std::to_string(y - o7*(2*(y-y1))) + "\n";
      temp = {x - o36*(2*(x-x1)), y - o7*(2*(y-y1))};
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

std::pair<int,int> bresenhamstep(int x1, int y1, int x2, int y2){
   if (x1==x2){
      int dir = (y2-y1)/abs(y2-y1);
      return {x1,y1+dir};
   }
   else{
   float m = slope(x1,y1,x2,y2);
   
   if (abs(m)<= 1) {
      return bresenham1step(x1,y1,x2,y2);
   }
   else{
      return bresenham2step(x1,y1,x2,y2);
   }
   }
}

/*

int main () {
    //file

    int x0, y0, x1, x2, y1, y2;

    std::cout << "Enter x1, y1, x2, y2:" << std::endl;
    std::cin >> x1 >> y1 >> x2 >> y2;

    bresenham(x1,y1,x2,y2,"test.csv");
   
    return 0;
}

*/