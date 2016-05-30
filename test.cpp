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
    int mtrSp = 50;
    int check = 0;
    int white_threshold = 130;//Threshold of white, i.e. from the 0 to 255 only values above this are detected
    float kP = 0.2;//Prop constant which scales with error signal
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
        int left = 0;       //True if line is left
        int right = 0;      //True if line is right
        int top = 0;        //True if line is forward
        int leftSum = 0;    //Totals amount of left mid pixels which are white
        int rightSum = 0;   //Totals amount of right mid pixels which are white
        int topSum = 0;     //Totals amount of top mid pixels which are white
        //Totals amount of top mid pixels which are white
        take_picture();
        for(int i = 0; i < 200; i++){  //For loop to save pixels to arrays and test whiteness, iterates through from a base value to reach a max
            //For left and right, this is from row 100 to row 215, column 1 and 319 respectively 
            //For top this is from 
                int leftSide = get_pixel(40, i, 3);//Saves the value of the left-mid pixels if above threshold
                if(leftSide > 130){
                  leftSum = leftSum + 1;//Adds to a total count of pixels that are white
                }
                else{//If not valid pixel skip
                  leftSum = leftSum + 0;
                }
                
                int rightSide = get_pixel(280, i, 3);//Saves the value of the right-mid pixels if above threshold
                if(rightSide > 130){
                  rightSum = rightSum + 1;//Adds to a total count of pixels that are white
                }
                else{//If not valid pixel skip
                  rightSum = rightSum + 0;
                }
                
            }
            if(leftSum > 40){left = 1;}
            else{left = 0;}
            if(rightSum > 40){right = 1;}
            else{right = 0;}
            if(topSum > 20){top = 1;}
            else{top = 0;}
        for(int i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
            sum = get_pixel(i, 1, 3);//Gets pixel at row 1 as it goes from 1 to 240
                if(sum > 130){  //If value greater than threshold make it 1 and add to num
                    w = 1;
                    num++; //num increases when a white pixel is found
                    topSum = topSum + 1;
                    }else{
                        w = 0;
                    }
                    totalSum = totalSum + ((i - 160) * w);//Takes the position of the i and adds to a total
        }
        printf("num %d\n", num);
            if(num > 310){
                int check = check + 1;
                        printf("Check %d\n", check);
                        //mtrSp = 40;
                        if(check > 6){
                            while(1){
                                if(left == 1 && right == 1){ //T intersection (choose left)
                                    set_motor(1, 0);
                                    set_motor(2, -55);
                                    Sleep(0, 500000);
                                    set_motor(1, 0);
                                    set_motor(2, 0);
                                }
                                else if(left == 0 && right == 1){ //Right side turn
                                  printf("Right %d\n", right);
                                    set_motor(2,0);
                                    set_motor(1, 55);
                                    Sleep(0, 500000);
                                    set_motor(2,0);
                                    set_motor(1, 0);
                                }
                                else if(num < 20){ //If not enough pixels are found, reverse and reset
                                    set_motor(1, -40.5);
                                    set_motor(2, 40);
                                    Sleep(0, 50000);
                                    continue;
                                }
                                    int totalSum = 0;
                                    int pSignal = 0;
                                    int dSignal = 0;
                                    int sum = 0;
                                    int num = 0;
                                    int eValue = 0;
                                    int w = 0;  
                                    int left = 0;       //True if line is left
                                    int right = 0;      //True if line is right
                                    int top = 0;        //True if line is forward
                                    int leftSum = 0;    //Totals amount of left mid pixels which are white
                                    int rightSum = 0;   //Totals amount of right mid pixels which are white
                                    int topSum = 0;     //Totals amount of top mid pixels which are white
                                    //Totals amount of top mid pixels which are white
                                    take_picture();
                                    for(int i = 0; i < 200; i++){  //For loop to save pixels to arrays and test whiteness, iterates through from a base value to reach a max
                                        //For left and right, this is from row 100 to row 215, column 1 and 319 respectively 
                                        //For top this is from 
                                            int leftSide = get_pixel(40, i, 3);//Saves the value of the left-mid pixels if above threshold
                                            if(leftSide > 130){
                                              leftSum = leftSum + 1;//Adds to a total count of pixels that are white
                                            }
                                            else{//If not valid pixel skip
                                              leftSum = leftSum + 0;
                                            }
                                            
                                            int rightSide = get_pixel(280, i, 3);//Saves the value of the right-mid pixels if above threshold
                                            if(rightSide > 130){
                                              rightSum = rightSum + 1;//Adds to a total count of pixels that are white
                                            }
                                            else{//If not valid pixel skip
                                              rightSum = rightSum + 0;
                                            }
                                            
                                        }
                                        if(leftSum > 40){left = 1;}
                                        else{left = 0;}
                                        if(rightSum > 40){right = 1;}
                                        else{right = 0;}
                                        if(topSum > 20){top = 1;}
                                        else{top = 0;}
                                        for(int i = 0; i < 320; i++){  /**Less than 320 as the image is 320 pixels across*/
                                        sum = get_pixel(i, 1, 3);//Gets pixel at row 1 as it goes from 1 to 240
                                            if(sum > 130){  //If value greater than threshold make it 1 and add to num
                                        w = 1;
                                        num++; //num increases when a white pixel is found
                                        topSum = topSum + 1;
                                        }else{
                                            w = 0;
                                        }
                                        totalSum = totalSum + ((i - 160) * w);//Takes the position of the i and adds to a total
                                    }
                            }
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
                        set_motor(1, mtrSp);
                        if(-(mtrSp + 0.5) + pSignal + dSignal <= 0){
                        set_motor(2, -(mtrSp + 0.5) + pSignal + dSignal);
                        }else{
                            set_motor(2, 0);
                        }
                        Sleep(0, 5000);
                    }
                    else if(pSignal < 0){/**left*/
                        //printf("left %d\n", pSignal);
                        if(mtrSp + pSignal + dSignal >= 0){
                        set_motor(1, mtrSp + pSignal + dSignal);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                        }
                        else{
                            set_motor(1, 0);
                        }
                        set_motor(2, -(mtrSp + 0.5));/**Minuses values if signal is minus it is double negative therefore positive*/
                        Sleep(0, 5000);
                    }
                }
        
            }

        return 0;
    }
