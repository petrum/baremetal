#include "../gpio.h"
#include "../misc.h"

void rgb();
void init(int);

volatile unsigned int* GPIO::gpio_;
//https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/
//int main(void) __attribute__((naked)); // w/o this it doesn't work when booted directly (no u-boot)

void color(int);

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
        for (int i = 0; i != 8; ++i)
        {
            color(i);
            for (int m = 0; m != 18; ++m)
                longDelay();
        }
    }
}

void init(int i)
{    
    GPIO::setMode(i, GPIO::Out);
    GPIO::setPUD(i, GPIO::PullOff);
    GPIO::off(i);
}

void color(int i)
{
    if (i % 2)
        GPIO::on(17);
    else
        GPIO::off(17);
    i = i >> 1;

    if (i % 2)
        GPIO::on(27);
    else
        GPIO::off(27);
    i = i >> 1;

    if (i % 2)
        GPIO::on(22);
    else
        GPIO::off(22);
}
