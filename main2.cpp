# include <stdio.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int open_screen_stream();
extern "C" int update_screen();

int main (){
init();

int sum = 0;      
int white_threshold = 60; 
/**Value pixels need to be over to be considered "white"*/
int w = 0;
int totalSum = 0; 
int num = 0;
float kP = 0.7;
int pSignal = 0;
int z = 0;
/**P in PID
float kD = 5.0;
D in PID
int pastError = 0;
int currentError = 0;*/
int eValue = 0;
int pError = 0;
//change speed to make it go through gate, then use that as baseline

while(z < 200){
    take_picture();
        for(int i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
            sum = get_pixel(i, 1, 3);
                if(sum > white_threshold){  
                    w = 1;
                    num++;
                }
                else{
                    w = 0;
                }
            totalSum = totalSum + ((i - 160) * w);
            
        }
    
        if(num < 18){
                set_motor(1, -35);/**Minuses values if signal is minus it is double negative therefore positive*/
               set_motor(2, 35.5);
                Sleep(0, 500000);
                continue;
        }
        else if(num != 0){
            eValue = totalSum/num;
            pSignal = eValue*kP;
        printf("pSignal %d\n", pSignal);
        /**currentError = abs(eValue);
        https://github.com/kaiwhata/ENGR101-2016/wiki/PID-(Proportional-Integral-Derivative)-Control
        dSignal = (currentError-pastError/x)*kD; <-- need to work out value for X*/
        //pError = eValue;
            if(pSignal > 0){/**right*/
            printf("right %d\n", pSignal);
                set_motor(1, (35 + pSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                set_motor(2, -35.5);
                Sleep(0, 100000);
            }
            else if(pSignal < 0){/**Prioritises left turns first*/
            printf("left %d\n", pSignal);
                set_motor(1, 35);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                set_motor(2, -(35.5 - pSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                Sleep(0, 100000);
            }
            z++;
        }

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
 * */
    return 0;
}


