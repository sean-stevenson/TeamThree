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

int main (){
init();
int pSignal = 0;
int sum = 0;      /**the white line*/
int white_threshold = 100;
int i;
int w;
int totalSum = 0;
int numfound = 0;

float kP = 0.3;
while(1==1){
    take_picture();
        for(i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
            sum = get_pixel(120,i,3);
                if(sum > white_threshold){  
                    w = 1;
                }
                else{
                    w = 0;
                }
            totalSum = totalSum + (i - 160) * w;
        }
        signalE = 160 - totalSum;
        P = kP * signalE;
        motorS = abs(totalSum);
            if(pSignal < 0){//left
                set_motor(1, motorS);//maybe need a constant instead
                set_motor(2,-1 * motorS + P);
                Sleep(0, 100000);
            }
            else if(pSignal > 0){//right
                set_motor(1, motorS + P);
                set_motor(2,-1 * motorS);
                Sleep(0, 100000);
            }
}
    return 0;
}
