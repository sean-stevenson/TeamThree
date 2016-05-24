# include <stdio.h>

extern "C" int init(int dl);
extern "C" int set_motor(int motor, int speed);

int main(){
init(0);
set_motor(1, 0);
set_motor(2, 0);
return 0;
}
