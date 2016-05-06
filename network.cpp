#include <stdio.h> include <time.h>

extern "C" int init(int d_lev);
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

int main(){
    init(1);
    int doorOpen = openDoor();
    while(doorOpen != 0){
      doorOpen = openDoor();
    }
    //execute movement
}
