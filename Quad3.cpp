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

int z = 0;

while(z < 200){
