# include <stdio.h>
#include <stdlib.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/

extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int init();
extern "C" int connect_to_server(char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int openDoor();
int move();

int main (){
    init();
    //openDoor();
    move();
    return 0;
}

int openDoor(){
    if(connect_to_server("130.195.6.196", 1024) == 0){
        send_to_server("Please");
        char message[24];
        receive_from_server(message);
        send_to_server(message);
        return 0;
    }else{return 1;}
}

int move(){
    int check = 0;
    int white_threshold = 130;//Threshold of white, i.e. from the 0 to 255 only values above this are detected
    float kP = 0.22;//Prop constant which scales with error signal
    float kD = 0.00015;
    int pastError = 0;//Past error to work out kD
    int currentError = 0;//Absolute of error signal - will need to check that works
    int eValue = 0;//Average value of error either side
    //Sleep(2,0); //For gate
    while(1){
        int totalSum = 0;
        int pSignal = 0;
        int dSignal = 0;
        int sum = 0;
        int num = 0;
        int eValue = 0;
        int w = 0;  
        //Totals amount of top mid pixels which are white
        take_picture();
        for(int i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
            sum = get_pixel(i, 1, 3);//Gets pixel at row 1 as it goes from 1 to 240
                if(sum > 130){  //If value greater than threshold make it 1 and add to num
                    w = 1;
                    num++; //num increases when a white pixel is found
                    }else{
                        w = 0;
                    }
                    totalSum = totalSum + ((i - 160) * w);//Takes the position of the i and adds to a total
        }
            if(num > 319){
                        int check = check + 1;
                        if(check > 1){ //T intersection (choose left)
                            set_motor(1, 0);
                            set_motor(2, -50);
                            Sleep(0, 500000);
                            set_motor(1, 0);
                            set_motor(2, 0);
                        }       
               }
            else if(num < 20){ //If not enough pixels are found, reverse and reset
                    set_motor(1, -40.5);
                    set_motor(2, 40);
                    Sleep(0, 50000);
                    continue;
            }
            else{
                    eValue = totalSum/num;//Finds average of a point at
                    pSignal = eValue*kP;//Times it by kP to get a value scaled with the e sginal
                    currentError = abs(eValue);
                    dSignal = abs(((currentError - pastError)/0.005)*kD);
                    pastError = currentError;

                    if(pSignal > 0){/**right*/
                        //printf("right %d\n", pSignal);
                        set_motor(1, 50);
                        if(-50.5 + pSignal + dSignal <= 0){
                        set_motor(2, -50.5 + pSignal + dSignal);
                        }else{
                            set_motor(2, 0);
                        }
                        Sleep(0, 5000);
                    }else if(pSignal < 0){/**left*/
                        //printf("left %d\n", pSignal);
                        if(50 + pSignal + dSignal >= 0){
                        set_motor(1, 50 + pSignal + dSignal);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                        }else{
                            set_motor(1, 0);
                        }
                        set_motor(2, -50.5);/**Minuses values if signal is minus it is double negative therefore positive*/
                        Sleep(0, 5000);
                    }
                }
        
            }

        return 0;
    }
