# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED
int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
   init();
   // Sets the motor connected to pin 1 to rotate
   // in one direction at MAX speed .

   //
   set_motor (1, 255);   /** 1 = left*/

   set_motor(2, -255);/** 2 = right wheel*/
   Sleep(0 ,500000);

return 0;}

//Some rough code to move along the line of tape, developed from the lecture
int take_picture();
int sum = 0;      /**the white line*/
int i;
//error here at the "for"
for(i = 0, i < 320, i++){  /**Less than 320 as the image is 320 pixels across*/

int col = get_pixel(120,i,3);

if(col < 220){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
    col = 0;
}
else{
    col = 1;
}
   sum = sum + (i)*col;  /**Traverses the pixels along row 120, in increments, using 0-160-320 as the boundaries*/

/** currently when between 150 and 160 it will go forward. Need to fine tune this deciding when to go straight*/
if(sum <= 160 && sum >= 150){        /**Fine tuned points where robot travels, will need to be tested*/
move_forward();
}

else if(sum < 150){    /**Fine tuned points where robot travels, will need to be tested*/
      turn_left();          /**Needs to be improved/made a method that works with the magnitude of sum to dictate how much it turns*/
}

else if(sum > 160){
      turn_right();     /**Needs to be improved/made a method that works with the magnitude of sum to dictate how much it turns*/
}
}

int move_Forward(void){
set_motor(1,200);
set_motor(2, -200);

}
int turn_left(void){
//turns right wheel but not left, hopefully turning it left.
set_motor(2, -100);
Sleep(0,500000);
}

int turn_right(void){
//turns left wheel, not right, turning it right
set_motor(1, -100);
Sleep(0,500000);
}

//Updated code
# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED 
extern "C" char get_pixel(int row, int col, int color);
int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
   init();
   // Sets the motor connected to pin 1 to rotate
   // in one direction at MAX speed .
   int take_picture();

int sum = 0;      /**the white line*/
int i;

for(i = 0; i < 16; i++){  /**Less than 320 as the image is 320 pixels across*/

col[i] = get_pixel(320/16 * i,120,3);
if(col[i] < 220){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
    white_threshold[i] = 1;
}else{
    white_threshold[i] = 0;
}

if(white_threshold[5] == 1 && white_threshold[9] == 1){        /**Fine tuned points where robot travels, will need to be tested*/
      move_forward();
}else if(white_threshold[5]){    /**0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 <-- pixel array taken to determine if a point is white or not, traverse to find if a section of the picture is white*/
      turn_left();          
}else if(sum > 160){
      turn_right();     
}
}



return 0;}

/**ROUGH CODES FOR MOVEMENT*/

int turn_left(void){

//while(sum < 160 || sum > 160){
//if(sum != 160){
set_motor(2,-100);
Sleep(0,500000);
}

int turn_right(void){

set_motor(1,100);
Sleep(0,500000);
}

int move_forward(void){
set_motor(1,200);
set_motor(2,-200);

}

