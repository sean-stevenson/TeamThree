# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int dir , int speed ); //THIS METHOD IS PARTIAL TO CHANGE FOR NEXT WEEK, MOST LIKELY NO dir parameter.
int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
   init();
   // Sets the motor connected to pin 1 to rotate
   // in one direction at MAX speed .
   set_motor (1, 1, 255);

   set_motor(2, 2, 255);
   Sleep(0 ,500000);




return 0;}
