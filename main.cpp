# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED
extern "C" int take_picture();

typedef int bool;
#define true 1
#define false 0

int main (){
init();
int sum = 0;      /**the white line*/
int white_threshold[16];
int col[16];
int i;
int w;

int kp = 0;
int pSignal = 0;

while(1){
take_picture();
for(i = 0; i < 16; i++){  /**Less than 320 as the image is 320 pixels across*/

col[i] = get_pixel(320/16 * i,120,3);
    if(col[i] > 190){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
        white_threshold[i] = 1; //assigns 1 where line is located
    }else{
        white_threshold[i] = 0; //assigns 0 to where it is more black
    }
    sum = sum + (i - 7.5) * white_threshold[i]; //will find a value that is either positive or negative, which will determine how far away from the line it is and which side of line.
    pSignal = sum * kp; 
    if(sum < 0){//left
        set_motor(1, pSignal);//need to work out which is which motor
    }
    else if(sum > 0){//right
    set_motor(2,-1 * pSignal);//need to work out which is which motor
        
    }
    else{
        set_motor(1, pSignal);
        set_motor(2,-1 * pSignal);
    }
    }
    return 0;
    }
//int move_forward(void){ //depending on pSignal the motors will be set to follow the line. Currently only prototype, still needs work.
    
    //}
