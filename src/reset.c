#include "pca9685.h"
#include <wiringPi.h>


#define PIN_BASE 300


int main(void)
{
    // Calling wiringPi setup first.
    wiringPiSetup();

    int fd = pca9685Setup(PIN_BASE, 0x40, 0);

    // If valid, turn off
    if (fd >= 0)
        pca9685PWMReset(fd);

    return fd;
}
