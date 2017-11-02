#include "../gpio.h"
#include "../misc.h"

void rgb();
void init(int);

volatile unsigned int* GPIO::gpio_;
//https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/
//int main(void) __attribute__((naked)); // w/o this it doesn't work when booted directly (no u-boot)
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);

    init(17); // red
    init(27); // green
    init(22); // blue
  
    while (true)
    {
        rgb();
        //longDelay();
        //longDelay();
    }
}

void init(int i)
{    
    GPIO::setMode(i, GPIO::Out);
    GPIO::setPUD(i, GPIO::PullOff);
    GPIO::off(i);
}

void onoff(int i)
{
    GPIO::on(i);
    longDelay();
    GPIO::off(i);
    longDelay();
}

void rgb()
{
    onoff(17);
    onoff(27);
    onoff(22);
}
