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

    init(17);
    init(21);
    init(22);
  
    while (true)
    {
        rgb();
        longDelay();
        longDelay();
    }
}

void init(int i)
{    
    GPIO::setMode(i, GPIO::Out);
    GPIO::setPUD(i, GPIO::PullDown);
    GPIO::off(i);
}

void rgb()
{
    GPIO::on(17);
    shortDelay();

    GPIO::off(17);
    GPIO::on(21);
    shortDelay();

    GPIO::off(21);
    GPIO::on(22);
    shortDelay();

    GPIO::off(22);
}
