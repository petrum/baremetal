volatile unsigned int* gpio;
volatile unsigned int tim;

int main(void) __attribute__((naked));
int main(void)
{
    gpio = (unsigned int*)0x20200000;

    /* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
       peripheral register to enable GPIO16 as an output */
    gpio[1] |= (1 << 18);

    while (1)
    {
        for(tim = 0; tim < 500000; tim++)
            ;

        /* Set the LED GPIO pin low ( Turn OK LED on for original Pi, and off for plus models )*/
        gpio[10] = (1 << 15);

        for(tim = 0; tim < 500000; tim++)
            ;
        /* Set the LED GPIO pin high ( Turn OK LED off for original Pi, and on for plus models )*/
        gpio[7] = (1 << 15);
    }
}
