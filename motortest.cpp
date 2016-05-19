# include <stdio.h>
# include <time.h>
/**these load specific methods from the ENGR101 library*/
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed );
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int open_screen_stream();
extern "C" int update_screen();

int main (){
init();
int z = 0;
int q = 0;
    while(z< 100){
    
                set_motor(1, 35);
                set_motor(2, -35.5);
                Sleep(0, 500000);
                z++;
                }
                set_motor(1, 0);
                set_motor(2, 0);
                return 0;
}
