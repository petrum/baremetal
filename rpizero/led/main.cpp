#include "../gpio.h"
#include "../misc.h"

void dot()
{
    GPIO::on(47);
    shortDelay();
    GPIO::off(47);
    shortDelay(); 
}

void line()
{
    GPIO::on(47);
    longDelay();
    GPIO::off(47);
    shortDelay(); 
}

void sos()
{
    dot();
    dot();
    dot();
    line();
    line();
    line();
    dot();
    dot();
    dot();
}

volatile unsigned int* GPIO::gpio_;
//https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/
int main(void) __attribute__((naked)); // w/o this it doesn't work when booted directly (no u-boot)
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);
    // the activity LED (green) is connected to GPIO 47
    GPIO::setMode(47, GPIO::Out);
    while (true)
    {
        sos();
        longDelay();
        longDelay();
    }
}
