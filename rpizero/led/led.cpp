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
    delay(30000000);
}

volatile unsigned int* gpio;

void off()
{
    gpio[8] = (1 << 15);
}

void on()
{
    gpio[11] = (1 << 15);
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

#define ARM_AUX_CONTROL_SMP	(1 << 6)

#define ARM_CONTROL_BRANCH_PREDICTION	   (1 << 11)
#define ARM_CONTROL_L1_INSTRUCTION_CACHE   (1 << 12)

void enableL1Cache()
{
    unsigned int nControl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  0" : "=r" (nControl));
    nControl |= (1 << 11) | (1 << 12);
    asm volatile ("mcr p15, 0, %0, c1, c0,  0" : : "r" (nControl) : "memory");    
}

void enableBranchPrediction()
{
    unsigned int nAuxControl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  1" : "=r" (nAuxControl));
    nAuxControl |= 1 << 11;
    asm volatile ("mcr p15, 0, %0, c1, c0,  1" : : "r" (nAuxControl));   // SMP bit must be set according to ARM TRM    
}

int main(void) __attribute__((naked)); // w/o this doesn't work when booted directly (no u-boot)
int main(void)
{
    gpio = (unsigned int*)0x20200000;
    enableBranchPrediction();
    enableL1Cache();

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
