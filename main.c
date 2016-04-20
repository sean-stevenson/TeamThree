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

/**Some rough code to move along the line of tape, developed from the lecture
 * take_picture();
 * int sum = 0;
 * int i;
 * (i = 0, i < 320, i++){//Less than 320 as the image is 320 pixels across
 * int col = get_pixel(120,i,3);
 *    if(w < 230){//checks the color recieved is enough "white" so no glossy surfaces are detected
         w = 0;
      }
      else{
         w = 1;
      }
      sum = sum + (i-160)*w;//Traverses the pixels along row 120, in increments, using -160_0_160 as the boundaries
     if(sum > 0){
       turn_left();//Needs to be improved/made a method
     {
     else if(sum < 0){
      turn_right();//Needs to be improved/made a method
     {
     else if(sum == 1)
      set_motor(1,1,255)
      set_motor(2,1,255)
     }
