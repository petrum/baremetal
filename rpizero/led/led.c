volatile unsigned int* gpio;
volatile unsigned int tim;

int main(void) __attribute__((naked));
int main(void)
{
    gpio = (unsigned int*)0x20200000;
    unsigned int ra;
    ra = gpio[4];
    ra &= ~(7<<21);
    ra |= 1<<21;
    gpio[4] = ra;

    while (1)
    {
        for(tim = 0; tim < 5000000; tim++)
            ;

        /* Set the LED GPIO pin low ( Turn OK LED on for original Pi, and off for plus models )*/
        gpio[8] = (1 << 15);

        for(tim = 0; tim < 5000000; tim++)
            ;
        /* Set the LED GPIO pin high ( Turn OK LED off for original Pi, and on for plus models )*/
        gpio[11] = (1 << 15);
    }
}