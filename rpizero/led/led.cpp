#include "../gpio.h"

void delay(int i)
{
    for(volatile int tim = 0; tim < i; tim++)
        ;   
}

void shortDelay()
{
    delay(10000000);
}

void longDelay()
{
    for (int i = 0; i != 3; ++i)
        shortDelay();
}

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

//https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=98904#p689471
void enableBranchPrediction()
{
    unsigned int nAuxControl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  1" : "=r" (nAuxControl));
    nAuxControl |= 1 << 11;
    asm volatile ("mcr p15, 0, %0, c1, c0,  1" : : "r" (nAuxControl));   // SMP bit must be set according to ARM TRM    
}

void enableL1Cache()
{
    unsigned int nControl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  0" : "=r" (nControl));
    nControl |= 1 << 12;
    asm volatile ("mcr p15, 0, %0, c1, c0,  0" : : "r" (nControl) : "memory");    
}

volatile unsigned int* GPIO::gpio_;
//https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/
int main(void) __attribute__((naked)); // w/o this it doesn't work when booted directly (no u-boot)
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);
    GPIO::setMode(47, GPIO::Out);
    while (true)
    {
        sos();
        longDelay();
        longDelay();
    }
}
