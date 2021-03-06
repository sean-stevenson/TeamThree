# include <stdio.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);

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

