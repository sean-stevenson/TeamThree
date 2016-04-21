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

   set_motor(2, 1, 255);
   Sleep(0 ,500000);




return 0;}

/**Some rough code to move along the line of tape, developed from the lecture
 * take_picture();
 * int sum = 0;
 * int i;
 * (i = 0, i < 320, i++){//Less than 320 as the image is 320 pixels across
 * int col = get_pixel(120,i,3);
 *    if(col < 220){//checks the color recieved is enough "white" so no glossy surfaces are detected
         col = 0;
      }
      else{
         col = 1;
      }
      sum = sum + (i)*col;//Traverses the pixels along row 120, in increments, using -160_0_160 as the boundaries
     if(sum > 160){//Fine tuned points where robot travels, will need to be tested
       turn_right();//Needs to be improved/made a method that works with the magnitude of sum to dictate how much it turns
     {
     else if(sum < 160){//Fine tuned points where robot travels, will need to be tested
      turn_left();//Needs to be improved/made a method that works with the magnitude of sum to dictate how much it turns
     {
     else if(sum == 160){
      set_motor(1,1,200)
      set_motor(2,1,200)
     }
}
