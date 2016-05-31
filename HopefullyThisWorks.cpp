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
    }else{
        return 1;
    }
}


int move(){
int white_threshold = 130;//Threshold of white, i.e. from the 0 to 255 only values above this are detected
int w = 0;
float kP = 0.2;//Prop constant which scales with error signal
float kD = 0.00015;
int pastError = 0;//Past error to work out kD
int currentError = 0;//Absolute of error signal - will need to check that works
Sleep(2,0);
while(1){
    int totalSum = 0;
    int pSignal = 0;
    int dSignal = 0;
    int sum = 0;
    int num = 0;
    int eValue = 0;
    take_picture();//Takes picture and sets all the variables to 0
    for(int i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
        sum = get_pixel(i, 1, 3);//Gets pixel at row 1 as it goes from 1 to 240
        if(sum > white_threshold){  //If value greater than threshold make it 1 and add to num
            w = 1;
            num++; //num increases when a white pixel is found
        }else{
            w = 0;
        }
        totalSum = totalSum + ((i - 160) * w);//Takes the position of the i and adds to a total
    }
    if(num < 20){ 
        set_motor(1, -40.5);
        set_motor(2, 40);
        Sleep(0, 50000);
        continue;
    //PID
    }else if(num != 0){
        eValue = totalSum/num;//Finds average of a point at
        pSignal = eValue*kP;//Times it by kP to get a value scaled with the e sginal
        currentError = abs(eValue);
        dSignal = abs(((currentError - pastError)/0.005)*kD);
        pastError = currentError;
        //Turn right
        if(pSignal > 0){
            set_motor(1, 40);
            if(-40.5 + pSignal + dSignal <= 0){
                set_motor(2,-(40.5 + pSignal + dSignal));
            }else{
                set_motor(2,0);
            }
            Sleep(0, 5000);
        //Turn left
        }else if(pSignal < 0){/**left*/
            if(40 + pSignal + dSignal >= 0){
                set_motor(1, 40 + pSignal + dSignal);
            }else{
                set_motor(1,0);
            }
            set_motor(2, -40.5);
            Sleep(0, 5000);
        }
    }

    if(num > 315){       //True if line is forward
        int leftSum = 0;    //Totals amount of left mid pixels which are white
        int rightSum = 0;   //Totals amount of right mid pixels which are white
        int topSum = 0;     //Totals amount of top mid pixels which are white

        for(int i = 0; i < 115; i++){  //For loop to save pixels to arrays and test whiteness, iterates through from a base value to reach a max
            int leftSide = get_pixel(1, 120 + i, 3);//Saves the value of the left-mid pixels if above threshold
            if(leftSide > 100){
                leftSum = leftSum + 1;//Adds to a total count of pixels that are white
            }else{//If not valid pixel skip
                leftSum = leftSum + 0;
            }

            int rightSide = get_pixel(319, 120 + i, 3);//Saves the value of the right-mid pixels if above threshold
            if(rightSide > 100){
                rightSum = rightSum + 1;//Adds to a total count of pixels that are white
            }else{//If not valid pixel skip
                rightSum = rightSum + 0;
            }
            
            int topSide = get_pixel(106 + i, 10, 3);//Saves the value of the top-mid pixels if above threshold
            if(topSide > 100){
                topSum = topSum + 1;//Adds to a total count of pixels that are white
            }else{//If not valid pixel skip
                topSum = topSum + 0;
            }
        }
        printf("TopSum %d\n", topSum);
        printf("RightSum %d\n", rightSum);
        printf("LeftSum %d\n", leftSum);
        //Skip left if theres line forward
        if((leftSum > rightSum) && (topSum > 100)){
            printf("Skip left");
            set_motor(1, 55);
            set_motor(2,-55);
            Sleep(0, 500000);
        }
        //Skip right if theres line forward
        if ((leftSum < rightSum) && (topSum > 100)){
            printf("Skip right");
            set_motor(1, 55);
            set_motor(2,-55);
            Sleep(0, 500000);
        }
        //4 way intersect just moves forward
        if((leftSum > 100) && (rightSum > 100) && (topSum > 100)){
            printf("4 way");
            set_motor(1, 55);
            set_motor(2,-55);
            Sleep(0, 500000);
        }
        //T-intersect
        else if((leftSum > 100) && (rightSum > 100) && (topSum < 60)){
            printf("T-intersect");
            set_motor(1, 0);
            set_motor(2, -55);
            Sleep(0, 500000);
            set_motor(1, 0);
            set_motor(2, 0);
        }
        //Turn right
        else if((leftSum < rightSum) && (topSum < 70)){
            printf("Right");
            set_motor(1, 55);
            set_motor(2, 0);
            Sleep(0, 500000);
            set_motor(1, 0);
            set_motor(2, 0);
        }
        //Turn left
        else if((leftSum > rightSum) && (topSum < 70)){
            printf("Left");
            set_motor(1, 0);
            set_motor(2, -55);
            Sleep(0, 500000);
            set_motor(1, 0);
            set_motor(2, 0);
        }
    //Reverses
    }
}
return 0;
}
