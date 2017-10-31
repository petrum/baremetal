#include "../gpio.h"
#include "../misc.h"

void rgb();

volatile unsigned int* GPIO::gpio_;
//https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/
//int main(void) __attribute__((naked)); // w/o this it doesn't work when booted directly (no u-boot)
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);
    // the activity LED (green) is connected to GPIO 47
    GPIO::setMode(17, GPIO::Out);
    GPIO::setMode(21, GPIO::Out);
    GPIO::setMode(22, GPIO::Out);
    while (true)
    {
        rgb();
        longDelay();
        longDelay();
    }
}

void rgb()
{
}
