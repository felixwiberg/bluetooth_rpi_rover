#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "pca9685.h"
#include <wiringPi.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50


int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);

    wiringPiSetup();
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if(fd < 0){
        printf("Error in setup\n");
        return fd;
    }
    pca9685PWMReset(fd);

    // read data from the client
    int steer = 307;
    bool lleft = false;
    bool lright = false;
    while(1){
        memset(buf, 0, sizeof(buf));
        bytes_read = read(client, buf, sizeof(buf));
        printf("%d",bytes_read);
        if( bytes_read > 0 ) {
            if( buf[0] == 'a' & lleft ){
                    if (steer <= 10){
                        steer = 10;
                    }else{
                        steer -= 10;
                    }
                    lleft = true;
                    lright = false;
            }else if( buf[0] == 'a' & !lleft ){
                    steer = 307 - 10;
                    lleft = true;
                    lright = false;
            }
            if( buf[0] == 'd' & lright ){
                    if (steer >= 600){
                        steer = 600;
                    }else{
                        steer += 10;
                    }
                    lright = true;
                    lleft = false;
            }else if( buf[0] == 'd' & !lright ){
                    steer = 307 + 10;
                    lright = true;
                    lleft = false;
            }
            printf("steer: %d", steer);
            
            pwmWrite(PIN_BASE + 16, steer);
            delay(40);
            pwmWrite(PIN_BASE + 16, 308);
            printf("buf : [%s] \n", buf);
        }
    }

    
    // close connection

    pca9685PWMReset(fd);
    close(client);
    close(s);
    return 0;
}
