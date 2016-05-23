# include <stdio.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/
extern "C" int init(int dl);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int open_screen_stream();
extern "C" int update_screen();
extern "C" int close_screen_stream();

int sTime = 500000;
int dTime = 500000;
int speed = 20;
int uTurn = 15;

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

int main(){
  init(0);
  open_screen_stream();
  set_motor(1, 0);  //Stop motors
  set_motor(2, 0);
  Sleep(0, 200000); //Rest briefly
  take_picture();   //Update picture
  char contChar[100] = "y";
  
  while(contChar == "y"){
  int update_screen();
  printf("Do you wish to continue? (y/n)\n");
  scanf("%s", contChar);
  
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
  
    //If statements test whiteness of each pixel in array
    if(leftSide > 100){
      leftSum++;
    }
    if(rightSide > 100){
      rightSum++;
    }
    if(topSide > 100){
      topSum++;
    }
  }
  if(leftSum > 5){
    left = 1;
  }
  if(rightSum > 5){
    right = 1;
  }
  if(topSum > 5){
    top = 1;
  }
  
  if(left == 1 && right == 1 && top == 0){ //T intersection (choose left)
    lTurn();
    printf("T intersection\n");
    return 1;
  }else if(left == 0 && right == 1 && top == 0){ //Right side turn
    rTurn();
    printf("Right turn\n");
    return 1;
  }else if(left == 1 && right == 0 && top == 0){ //Left side turn
    lTurn();
    printf("Left turn\n");
    return 1;
  }else if(left == 0 && right == 0 && top == 0){ //Dead end (turn 180)
    dEnd();
    printf("Dead end\n");
    return 1;
  }else if(left == 1 && right == 1 && top == 1){ //4-way intersection (choose left path)
    lTurn();
    printf("4-way\n");
    return 1;
  }else if(left == 1 && right == 0 && top == 1){ //Right not available (choose left path)
    lTurn();
    printf("No right\n");
    return 1;
  }else if(left == 0 && right == 1 && top == 1){ //Left not available (choose forward)
    printf("No left\n");
    return 1;
  }else if(left == 0 && right == 0 && top == 1){ //Straight line
    printf("Straight  Line\n");
    return 1;
  }else{
    printf("Incorrect if statement found.\n");
    return 0;
  }
}
close_screen_stream();
}

