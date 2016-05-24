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
//left motor is connected to 1.
//right connected to 2.
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
int white_threshold = 120; 
int w = 0;
int num = 0;
float kP = 0.5;
//float kD = 1.2;
int pastError = 0;
int currentError = 0;
int eValue = 0;
/*
int doorOpen = openDoor();
while(doorOpen != 0){
        doorOpen = openDoor();
}
Sleep(3,0);
*/
while(1){
    take_picture();
    int totalSum = 0;
    int sum = 0;
    int pSignal = 0;
    int dSignal = 0;
    int num = 0;
        for(int i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
            sum = get_pixel(i, 1, 3);
                if(sum > white_threshold){  
                    w = 1;
                    num++; //num increases when a white pixel is found
                }
                else{
                    w = 0;
                }
            totalSum = totalSum + ((i - 160) * w);
        }
        if(num < 22){ //Low amount of white pixels found turn left?
                set_motor(1, -35);
                set_motor(2, 35.5);
                Sleep(0, 300000);
                continue;
        }
        else if(num != 0){
            eValue = totalSum/num;
            //pError = pSignal/4;
            pSignal = eValue*kP;
            //currentError = abs(eValue);
            //dSignal = (currentError /*-pastError*/)*kD;
            //pastError = eValue;
            if(pSignal > 0 && pSignal <120){/**right*/
                printf("right %d\n", pSignal);
                set_motor(1, (30 + pSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                // - dSignal
                set_motor(2, -30.5);
                //+ pSignal
                // + dSignal
                Sleep(0, 300000);
            }
            else if(pSignal > 120){
            printf("tighter right %d\n", pSignal);
                set_motor(1, (30 + pSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                // - dSignal
                set_motor(2, -15);
                //+ pSignal
                // + dSignal
                Sleep(0, 300000);
            }
            else if(pSignal < 0 && pSignal > -120){/**Prioritises left turns first*/
                printf("left %d\n", pSignal);
                set_motor(1, 30);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                //+ pSignal
                 //+ dSignal
                set_motor(2, -(30.5 - pSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                //- dSignal
                Sleep(0, 300000);
            }
            else if(pSignal < -120){
                printf("tighterleft %d\n", pSignal);
                set_motor(1, 15);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                //+ pSignal
                 //+ dSignal
                set_motor(2, -(30.5 - pSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                //- dSignal
                Sleep(0, 300000);
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


