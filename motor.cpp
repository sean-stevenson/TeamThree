# include <stdio.h>
# include <time.h>
//these load specific methods from the ENGR101 library
extern "C" int init();
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor( int motor , int speed ); //NOW FIXED
extern "C" char get_pixel(int row, int col, int color);

int main (){

    int take_picture();

    int whiteThreshold = 220;
    int pxCount = 16;               // This is the amount of pixels we will use from the photo
    int pixelColour[pxCount];   // Holds the value of the selected pixel (white[1]/black[0])
    int col[pxCount];
    int running = 1;



    while(running == 1){
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
    }
    return 0;
    }
}
