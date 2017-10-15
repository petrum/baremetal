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

    //https://raspberrypi.stackexchange.com/questions/39252/on-board-led-connection-to-gpio
    //the power LED (red) is connected to GPIO 35 (not present on the Pi Zero)
    //the activity LED (green) is connected to GPIO 47
    
    //http://www.susa.net/wordpress/2012/07/raspberry-pi-gpfsel-gpio-and-pads-status-viewer/
    //FSEL47 (GPFSEL4[21-23]) = 0 (GPIO In - [Low])
    //In == 0, Out == 1, ALT0-ALT5 from 2 to 7 (total of 8, of three available bits)
    gpio[4] = (gpio[4] & ~(7 << 21)) | 1 << 21;
    //FSEL35 (GPFSEL3[15-17]) = 0 (GPIO In - [Low]): 
    while (1)
    {
        sos();
        longDelay();
        longDelay();
    }
}
