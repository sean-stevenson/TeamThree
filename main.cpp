# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int open_screen_stream();
extern "C" int update_screen();

int turn_right(){
    set_motor(2,-1 * pSignal);//need to work out which is which motor
     printf("Right %d\n", pSignal);
}

int turn_left(){
     set_motor(1, pSignal);//need to work out which is which motor
         printf("Left %d\n", pSignal);
}

int main (){
init();
int sum = 0;      /**the white line*/
int white_threshold[16];
int col[16];
int i;
int w;



int kp = 0.5;
int pSignal = 0;
while(1==1){
take_picture();
for(i = 0; i < 16; i++){  /**Less than 320 as the image is 320 pixels across*/

    sum = get_pixel(320/16 * i,120,3);
    if(sum > 100){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
        white_threshold[i] = 1; //assigns 1 where line is located
    }
    else{
        white_threshold[i] = 0; //assigns 0 to where it is more black
    }
    sum = sum + ((i - 7) * white_threshold[i]); //will find a value that is either positive or negative, which will determine how far away from the line it is and which side of line.
    pSignal = sum * kp*8;
}
    
    for(int w = 0; w < 16; w++){
    if(sum < 0){//left
        turn_left();
    }
    if(sum > 0){//right
    turn_right();
        
    }
        set_motor(1, pSignal);
        set_motor(2,-1 * pSignal);
    
         printf("Forward %d\n", pSignal);
    }
   

     printf("Running \n");//testing speed value going to wheels for means of finding way to slow it down.
    
    }
    return 0;
}
