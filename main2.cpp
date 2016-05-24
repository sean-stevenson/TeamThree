# include <stdio.h>
#include <stdlib.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/

extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int init(int d_lev);
extern "C" int connect_to_server(char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int openDoor(){
    if(connect_to_server("130.195.6.196", 1024) == 0){
        send_to_server("Please");
        char message[24];
        receive_from_server(message);
        send_to_server(message);
        return 0;
    }else{
        return 1;
    }
}

int main (){
init(0);

int sum = 0;      
int white_threshold = 110; 
int w = 0;
int num = 0;
float kP = 0.8;
int pSignal = 0;
int dSignal = 0;
float kD = 5.0;
int pastError = 0;
int currentError = 0;
int eValue = 0;

int doorOpen = openDoor();
while(doorOpen != 0){
        doorOpen = openDoor();
}
Sleep(4,0);

while(1){
    take_picture();
    int totalSum = 0;
    int sum = 0;
    int pSignal = 0;
    int num = 0;
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
        if(num < 20){
                set_motor(1, -40);
                set_motor(2, 40.5);
                Sleep(0, 500000);
                continue;
        }
        else if(num != 0){
            eValue = totalSum/num;
            //pError = pSignal/4;
            pSignal = eValue*kP;
            currentError = abs(eValue);
            dSignal = (currentError-pastError)*kD;
            pastError = eValue;
            if(pSignal > 0){/**right*/
                printf("right %d\n", pSignal);
                set_motor(1, (35 + pSignal + dSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                set_motor(2, -35.5);
                Sleep(0, 500000);
            }
            else if(pSignal < 0){/**Prioritises left turns first*/
                printf("left %d\n", pSignal);
                set_motor(1, 35);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                set_motor(2, -35.5 - pSignal - dSignal);/**Minuses values if signal is minus it is double negative therefore positive*/
                Sleep(0, 500000);
            }
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
 set_motor(1, 0);
 set_motor(2, 0);
    return 0;
}


