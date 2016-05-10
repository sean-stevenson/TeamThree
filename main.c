//Updated code
# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED
extern "C" char get_pixel(int row, int col, int color);

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
    }else{
        return 1;
    }
}

int turn_left(void){
set_motor(2,-100);
Sleep(0,500000);
}

int turn_right(void){
set_motor(1,100);
Sleep(0,500000);
}

int move_forward(void){
set_motor(1,200);
set_motor(2,-200);
}

int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
   init();
int doorOpen = openDoor();
while(doorOpen != 0){
      doorOpen = openDoor();
    }
    //execute movement

   // Sets the motor connected to pin 1 to rotate
   // in one direction at MAX speed .
   int take_picture();

int sum = 0;      /**the white line*/
int i;
int w;
int kp;
int white_threshold[16];
int col[16];




for(i = 1; i < 16; i++){  /**Less than 320 as the image is 320 pixels across*/

col[i] = get_pixel(320/16 * i,120,3);
if(col[i] < 220){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
    white_threshold[i] = 1;
}else{
    white_threshold[i] = 0;
}
for(w = 0; w > 15; w++){

if(w > 8 && white_threshold[w] == 1){  /**Fine tuned points where robot travels, will need to be tested*/
      //kp = w/5;
      turn_right();
}else if(w < 7 && white_threshold[w] == 1){    /**0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 <-- pixel array taken to determine if a point is white or not, traverse to find if a section of the picture is white*/
      //kp = w/9; some constant that changes depending on where the array is at, if it is at the lower bounds it will be a greater value
      turn_left();
}else if((w == 8 || w == 7) && (white_threshold[w] = 1)){
      move_forward();
}
}
return 0;
}
}






