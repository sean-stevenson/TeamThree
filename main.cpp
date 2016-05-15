//Updated code
# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int connect_to_server(char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

#define PIXEL_COUNT 16

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

int turn_left(){
    set_motor(2,-50);
    set_motor(1,-50);
    Sleep(0, 100000);
    set_motor(1, 0);
    set_motor(2, 0);
}

int turn_right(){
    set_motor(1,50);
    set_motor(2,50);
    Sleep(0, 100000);
    set_motor(1, 0);
    set_motor(2, 0);
}

int move_forward(){
    set_motor(1,50);
    set_motor(2,-50);
    Sleep(0, 100000);
    set_motor(1, 0);
    set_motor(2, 0);
}

int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
    init();
    
    //int doorOpen = openDoor();
    //while(doorOpen != 0){
    //  doorOpen = openDoor();
    //}
    


    int whiteThreshold = 170;        // This is the amount of pixels we will use from the photo
    int pixelColour[PIXEL_COUNT];    // Holds the value of the selected pixel (white[1]/black[0])
    int col[PIXEL_COUNT];            // Holds the whiteness of (PIXEL_COUNT) pixels in the picture
    int running = 1;                 // This will be used to loop until the avc is finished
    int sum = 0;


    //while(running == 1){
    for(int time=0;time<20;time++){  
        
    take_picture();
    
    for(int i = 0; i < PIXEL_COUNT; i++){  /**Less than 320 as the image is 320 pixels across*/

            sum = get_pixel(320/PIXEL_COUNT * i,120,3);
            if(sum > whiteThreshold){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
                pixelColour[i] = 1;
            }else{
                pixelColour[i] = 0;
            }
        }
        for(int w = 0; w < PIXEL_COUNT; w++){

            if(pixelColour[(PIXEL_COUNT / 2)-1] == 1 || pixelColour[(PIXEL_COUNT / 2)+1 == 1]){
                move_forward();
                printf("F\n");
            }
            else if(w < (PIXEL_COUNT / 2)-2 && pixelColour[w] == 1){
                turn_left();
                printf("L\n");
            }
            else if(w > (PIXEL_COUNT / 2)+2 && pixelColour[w] == 1){  /**Fine tuned points where robot travels, will need to be tested*/
                turn_right();
                printf("R\n");
            }  
        }
        Sleep(0, 500000);
    }
    return 0;
}

   /**0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 <-- pixel array taken to determine if a point is white or not, traverse to find if a section of the picture is white*/
      //kp = w/9; some constant that changes depending on where the array is at, if it is at the lower bounds it will be a greater value





