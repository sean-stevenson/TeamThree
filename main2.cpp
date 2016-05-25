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

int sTime = 500000; //Sleep time for left/right turn
int dTime = 1000000; //Sleep time for dead end
int speed = 20;     //left/right turn speed
int uTurn = 15;     //Dead end turn speed

int lTurn(){  //Turn left 90 degrees
  set_motor(2, -speed);
  Sleep(0, sTime);
  set_motor(2, 0);
  return 0;
}

int rTurn(){  //Turn right 90 degrees
  set_motor(1, speed);
  Sleep(0, sTime);
  set_motor(1, 0);
  return 0;
}

int dEnd(){ //Turn 180 degrees clockwise
  set_motor(1, uTurn);
  set_motor(2, uTurn);
  Sleep(0, dTime);
  set_motor(1, 0);
  set_motor(2, 0);
  return 0;
} 

int intersection(){
  set_motor(1, 0);  //Stop motors
  set_motor(2, 0);
  Sleep(0, 200000); //Rest briefly
  take_picture();   //Update picture
  
  int left = 0;       //True if line is left
  int right = 0;      //True if line is right
  int top = 0;        //True if line is forward
  int leftSum = 0;    //Totals amount of left mid pixels which are white
  int rightSum = 0;   //Totals amount of right mid pixels which are white
  int topSum = 0;     //Totals amount of top mid pixels which are white
  
  
  for(int i = 0; i < 10; i++){  //For loop to save pixels to arrays and test whiteness
    int leftSide = get_pixel(0, 115 + i, 3);    //Saves the value of the left-mid pixels
    int rightSide = get_pixel(319, 125 + i, 3); //Saves the value of the right-mid pixels
    int topSide = get_pixel(155 + i, 0, 3);     //Saves the value of the top-mid pixels
  
    //If statements test whiteness of each pixel in array 100. Will be set to white_threshold when added to main
    if(leftSide/20 > 130){
      left = 1;
    }
    else{
      left = 0;
    }
    if(rightSide > 130){
      right = 1;
    }
    else{
      right = 0;
    }
    if(topSide > 130){
      top = 1;
    }
    else{
      top = 0;
    }
    }
  
  //If statements set left/right/top to 1 if the majority of their pixels are white
/* if(leftSum > 5){
    left = 1;
  }
  if(rightSum > 5){
    right = 1;
  }
  if(topSum > 5){
    top = 1;
  }*/
  
  //Main conditionals, returns 1 to the main function if sucessful
  if(left == 1 && right == 1 && top == 0){ //T intersection (choose left)
    lTurn();
    return 1;
  }else if(left == 0 && right == 1 && top == 0){ //Right side turn
    rTurn();
    return 1;
  }else if(left == 1 && right == 0 && top == 0){ //Left side turn
    lTurn();
    return 1;
  }else if(left == 0 && right == 0 && top == 0){ //Dead end (turn 180)
    dEnd();
    return 1;
  }else if(left == 1 && right == 1 && top == 1){ //4-way intersection (choose forwards path)
    return 1;
  }else if(left == 1 && right == 0 && top == 1){ //Right not available (choose forwards path)
    return 1;
  }else if(left == 0 && right == 1 && top == 1){ //Left not available (choose forward)
    return 1;
  }else if(left == 0 && right == 0 && top == 1){ //Straight line
    return 1;
  }else{
    println("Incorrect if statement found."); //This should never be called and means an if statement is coded incorrectly 
    return 0;
  }
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
                    
                }
                else{
                    w = 0;
                }
                totalSum = totalSum + ((i - 160) * w);//Takes the position of the i and adds to a total
        }
        if(num < 20){ //If not enough pixels are found, reverse and reset
                set_motor(1, -40.5);
                set_motor(2, 40);
                Sleep(0, 100000);
                continue;
        }
        else if(num > 310){
            intersection();
            continue;
        }
        else if(num != 0){
            printf("Num at T %d \n", num);
            eValue = totalSum/num;//Finds average of a point sat -130 or 50
            pSignal = eValue*kP;//Times it by kP to get a value scaled with the e sginal
            currentError = abs(eValue);
            printf("cError %d\n", currentError);
            exSignal = abs((currentError - pastError)*kD);
            dSignal = abs(((currentError - pastError)/0.005)*kD);
            printf("dSignal %d\n", dSignal);
            pastError = currentError;
            if(pSignal > 0){/**right*/
                printf("right %d\n", pSignal);
                set_motor(1, (35 + pSignal+dSignal));
                // + dSignal
                set_motor(2, -35.5);
                Sleep(0, 5000);
            }
            else if(pSignal < 0){/**left*/
                printf("left %d\n", pSignal);
                set_motor(1, 35);/**From a few calculations 40 seems roughly right, max value is 70ish*/
                set_motor(2, -(35.5 - pSignal + dSignal));/**Minuses values if signal is minus it is double negative therefore positive*/
                //+ dSignal
                Sleep(0, 5000);
            }
            
        }

}
return 0;
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
 * */
 

