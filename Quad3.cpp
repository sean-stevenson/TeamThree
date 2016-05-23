# include <stdio.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/
extern "C" int init();
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);

int left = 0; //Saves the value of the left-mid pixel
int right = 0;//Saves the value of the right-mid pixel
int top = 0;  //Saves the value of the top-mid pixel

int intersection(){

  take_picture();  
  left = get_pixel(0, 120, 3);
  right = get_pixel(319, 120, 3);
  top = get_pixel(160, 0, 3);
  
  if(left > 100 && right > 100 && top < 100){ //T intersection (choose left)
    lTurn();
  }else if(left < 100 && right > 100 && top < 100){ //Right side turn
    rTurn();
  }else if(left > 100 && right < 100 && top < 100){ //Left side turn
    lTurn();
  }else if(left < 100 && right < 100 && top < 100){ //Dead end (turn 180)
    dEnd();
  }else if(left > 100 && right > 100 && top > 100){ //4-way intersection (choose left path)
    lTurn();
  }else if(left > 100 && right < 100 && top > 100){ //Right not available (choose left path)
    lTurn();
  }else if(left < 100 && right > 100 && top < 100){ //Left not available (choose forward)
    return 0;
  }else if(left < 100 && right < 100 && top > 100){ //Straight line
    return 0;
  }else{
    println("Incorrect if statement found.");
    return 1;
  }
  return 0;
}

while(intersetion() == 1);

int lTurn(){
  set_motor(1, 0);
  set_motor(2, 0);
  Sleep(0, 500000);
  set_motor(2, -speed);
  Sleep(0, sTime);
  set_motor(2, 0);
}

int rTurn(){
  set_motor(1, 0);
  set_motor(2, 0);
  Sleep(0, 500000);
  set_motor(1, speed);
  Sleep(0, sTime);
  set_motor(1, 0);
}
