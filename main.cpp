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

int turn_left(){
    set_motor(2,-50);
}

int turn_right(){
    set_motor(1,50);
}

int move_forward(){
    set_motor(1,50);
    set_motor(2,-50);
}

int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
    init();
    
    //int doorOpen = openDoor();
    //while(doorOpen != 0){
    //  doorOpen = openDoor();
    //}
    


    int whiteThreshold = 220;
    int pxCount = 16;               // This is the amount of pixels we will use from the photo
    int pixelColour[pxCount];   // Holds the value of the selected pixel (white[1]/black[0])
    int col[pxCount];
    int running = 1;



    //while(running == 1){
    for(int time=0;time<20;time++){  
        
    int take_picture();
    
    for(int i = 0; i < pxCount; i++){  /**Less than 320 as the image is 320 pixels across*/

            col[i] = get_pixel(320/pxCount * i,120,3);
            if(col[i] > whiteThreshold){     /**checks the color recieved is enough "white" so no glossy surfaces are detected*/
                pixelColour[i] = 1;
            }else{
                pixelColour[i] = 0;
            }
        }
        for(int w = 0; w < pxCount; w++){

            if(pixelColour[(pxCount / 2)-1] == 1 || pixelColour[(pxCount / 2)+1 == 1]){
                move_forward();
            }
            else if(w < (pxCount / 2)-2 && pixelColour[w] == 1){
                turn_left();
            }
            else if(w > (pxCount / 2)+2 && pixelColour[w] == 1){  /**Fine tuned points where robot travels, will need to be tested*/
                turn_right();
            }  
        }
        Sleep(0, 500000);
    }
    return 0;
}

   /**0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 <-- pixel array taken to determine if a point is white or not, traverse to find if a section of the picture is white*/
      //kp = w/9; some constant that changes depending on where the array is at, if it is at the lower bounds it will be a greater value






