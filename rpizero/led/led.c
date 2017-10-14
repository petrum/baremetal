int main(void)
{
    unsigned int* gpio = (unsigned int*)0x20200000;
    volatile unsigned int tim;
    while (1)
    {
        for(tim = 0; tim < 5000000; tim++)
            ;
        gpio[8] = (1 << 15); // LED off
        for(tim = 0; tim < 20000000; tim++)
            ;
        gpio[11] = (1 << 15); // LED on
    }
}
