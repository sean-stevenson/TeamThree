#include <stdio.h>

extern "C" int init(int d_lev);
extern "C" int read_analog(int ch_adc);
extern "C" int select_IO(int chan, int direct);

int maze(){

  select_IO(0, 1);  //Assuming the left IR is in analogue 0
  select_IO(1, 1);  //And right is in 1
  
  int leftSensor = read_analog(0);  //The IR return a percentage (0 to 1)
  int rightSensor = read_analog(1); //Of the voltage passed through
  int expectedWallDistance = 0.3;    //This value is random at the moment and needs to be tested and changed
  
  if(leftSensor < expectedWallDistance){
    printf("Wall to left\n");
  }else{
    printf("No wall to left\n");
  }
  if(rightSensor < expectedWallDistance){
    printf("Wall to right\n");
  }else{
    printf("No wall to right\n");
  }
  return 0;
  
}

int main(){
  maze();
}

/*Possible code*/

error = left - right;

pSignal = error * kP;
pSignal = (pSignal/600)*100;
set_motor(1, 45 + pSignal);
set_motor(2, -45.5 - pSignal);
