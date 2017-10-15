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

volatile unsigned int* gpio;

void off()
{
    // the activity LED (green) is connected to GPIO 47
    gpio[8] = 1 << (47 - 32);
}

void on()
{
    gpio[11] = 1 << (47 - 32);
}

void dot()
{
    on(); shortDelay(); off(); shortDelay(); 
}

void line()
{
    on(); longDelay(); off(); shortDelay(); 
}

void sos()
{
    dot(); dot(); dot();
    line(); line(); line();
    dot(); dot(); dot();
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

//https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/
int main(void) __attribute__((naked)); // w/o this it doesn't work when booted directly (no u-boot)
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    gpio = (unsigned int*)0x20200000;
    unsigned int ra = gpio[4];
    ra &= ~(7 << 21);
    ra |= 1 << 21;
    gpio[4] = ra;

    while (1)
    {
        sos();
        longDelay();
        longDelay();
    }
}
