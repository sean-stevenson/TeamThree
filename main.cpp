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

int sum = 0;      /**the white line*/
int white_threshold = 100;
int i;
int w;
int totalSum = 0;
int num;
//P in PID
int kP = 0.3;
int pSignal = 0;
//D in PID
int previous_error = 0;
int current_error = 0;
int kd = 5.0;

while(1==1){
    take_picture();
        for(i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
            sum = get_pixel(120,i,3);
                if(sum > white_threshold){  
                    w = 1;//white value
                    num++;
                }
                else{
                    w = 0;//white value
                }
            totalSum = totalSum + (i - 160) * w;
        }
        eValue = totalSum/num;
        pSignal = eValue*kP
            if(pSignal < 0){//Prioritises left turns first
                set_motor(1, 35);//From a few calculations 40 seems roughly right, max value is 70ish
                set_motor(2,-1 * (35 - pSignal));//Minuses values if signal is minus it is double negative therefore positive
                Sleep(0, 100000);
            }
            else if(pSignal > 0){//right
                set_motor(1, (35 + pSignal));//Minuses values if signal is minus it is double negative therefore positive
                set_motor(2,-1 * 35);
                Sleep(0, 100000);
            }
}
    return 0;
}

/**Test case formatting
 * 
 * Test case 1:
 * Has 20 inputs, from values of i = 301 and i = 320 , averages to eValue = 150
 * pSignal = 150 * 0.3 = 45
 * pSignal is positive so turn right
 * Left motor = 80
 * Right motor = -35
 * 
 * Test case 2:
 * Has 17 inputs, from values of i = 147 and i = 162 , averages to eValue = 145
 * pSignal = -15 * 0.3 = -4.5
 * pSignal is negative so turn left
 * Left motor = 35
 * Right motor = -39.5
 * 
 * Test case 3:
 * Has 30 inputs, from values of i = 1 and i = 30, averages to eValue = -144.6
 * pSignal = -144.6 * 0.3 = -43.38
 * pSignal is negative so turn left
 * Left motor = 35
 * Right motor = -78.38
 * 
 * /
