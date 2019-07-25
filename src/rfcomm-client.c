#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "B8:27:EB:E2:69:DB";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send a message
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    while(1){
        int ch;
        char m[2];
        cbreak();
        nodelay(stdscr, TRUE);
        for (;;) {
            if ((ch = getch()) == ERR) {
                //printf("no response");
            }
            else {
                clear();
                printw("%c",ch);
                if(status == 0) {
                    m[0] = ch;
                    m[1] = '\0';
                    status = write(s, m, 1);
                }
                if(status < 0){
                    printw("\nerror");
                    perror("uh oh");
                }
            }
        }
        sleep(1);
    }

    close(s);
    return 0;
}

