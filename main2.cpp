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
int sum = 0;//get pixel value which returns values from 0 to 255 depending on the whiteness      
int white_threshold = 130;//Threshold of white, i.e. from the 0 to 255 only values above this are detected 
int w = 0;
int num = 0;
int exSignal = 0;
float kP = 0.133;//Prop constant which scales with error signal
float kD = 0.001;
int pastError = 0;//Past error to work out kD
int currentError = 0;//Absolute of error signal - will need to check that works
int eValue = 0;//Average value of error either side

//Sleep(2,0);
while(1){
    
    int totalSum = 0;
    int pSignal = 0;
    int dSignal = 0;
    int sum = 0;
    int num = 0;
    int eValue = 0;
    int left = 0;       //True if line is left
    int right = 0;      //True if line is right
    int top = 0;        //True if line is forward
    int leftSum = 0;    //Totals amount of left mid pixels which are white
    int rightSum = 0;   //Totals amount of right mid pixels which are white
    int topSum = 0;     //Totals amount of top mid pixels which are white
    
    take_picture();
    for(int i = 0; i < 200; i++){  //For loop to save pixels to arrays and test whiteness, iterates through from a base value to reach a max
            //For left and right, this is from row 100 to row 215, column 1 and 319 respectively 
            //For top this is from 
                int leftSide = get_pixel(1, 39+ i, 3);//Saves the value of the left-mid pixels if above threshold
                if(leftSide > 130){
                  leftSum = leftSum + 1;//Adds to a total count of pixels that are white
                }else{//If not valid pixel skip
                  leftSum = leftSum + 0;
                }
                
                int rightSide = get_pixel(319, 39 + i, 3);//Saves the value of the right-mid pixels if above threshold
                if(rightSide > 130){
                  rightSum = rightSum + 1;//Adds to a total count of pixels that are white
                }else{//If not valid pixel skip
                  rightSum = rightSum + 0;
                }
                
                int topSide = get_pixel(106 + i, 1, 3);//Saves the value of the top-mid pixels if above threshold
                if(topSide > 130){
                  topSum = topSum + 1;//Adds to a total count of pixels that are white
                }else{//If not valid pixel skip
                  topSum = topSum + 0;
                }
            }
            if(leftSum > 80){
                left = 1;
            }else{
                left = 0;
            }
            
            if(rightSum > 80){
                right = 1;
            }else{
                right = 0;
            }
            
            if(topSum > 80){
                top = 1;
            }else{
                top = 0;
            }
            
    //Takes picture and sets all the variables to 0
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
            printf("TopSum %d\n", topSum);
            printf("RightSum %d\n", rightSum);
            printf("LeftSum %d\n", leftSum);
        
        if(top != 1){
            if(left == 1 && right == 1 && top == 0){ //T intersection (choose left)
                // && top == 0
                set_motor(1, 0);
                set_motor(2, -40);
                Sleep(1, 0);
                set_motor(1,0);
                set_motor(2, 0);  
            }else if(left == 0 && right == 1 && top == 0){ //Right side turn
             //&& top == 0
                printf("Right");
                set_motor(2,0);
                set_motor(1, 40);
                Sleep(1, 0);
                set_motor(2,0);
                set_motor(1, 0);
            }else if(left == 1 && right == 0 && top == 0){ //Left side turn
            // && top == 0
                printf("Left");
                set_motor(1, 0);
                set_motor(2, -40);
                Sleep(1, 0);
                set_motor(1,0);
                set_motor(2, 0);
            } else if(num != 0){
                if(num < 20){ //If not enough pixels are found, reverse and reset
                set_motor(1, -40.5);
                set_motor(2, 40);
                Sleep(0, 50000);
                continue;
                }else{
                //printf("Num at T %d \n", num);
                eValue = totalSum/num;//Finds average of a point at
                pSignal = eValue*kP;//Times it by kP to get a value scaled with the e sginal
                currentError = abs(eValue);
                dSignal = abs(((currentError - pastError)/0.005)*kD);
                //printf("dSignal %d\n", dSignal);
                pastError = currentError;
            
            if(pSignal > 0){/**right*/
                //printf("right %d\n", pSignal);
                set_motor(1, (35 + pSignal+dSignal));
                // + dSignal
                set_motor(2, -35.5);
                Sleep(0, 5000);
            }else if(pSignal < 0){/**left*/
                //printf("left %d\n", pSignal);
                set_motor(1, 35);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                set_motor(2, -(35.5 - pSignal + dSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                //+ dSignal
                Sleep(0, 5000);
            }
            }
        }
    }

    return 0;
}
}

int main (){
init();
//openDoor();
move();
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
 *  //currentError = abs(eValue);
            //dSignal = (currentError -pastError)*kD;
            //pastError = eValue;
*/
 

