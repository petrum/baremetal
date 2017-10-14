void delay(int i)
{
    for(volatile int tim = 0; tim < i; tim++)
        ;   
}

int main(void)
{
    unsigned int* gpio = (unsigned int*)0x20200000;
    volatile unsigned int tim;
    while (1)
    {
        delay(5000000);
        gpio[8] = (1 << 15); // LED off
        delay(20000000);
        gpio[11] = (1 << 15); // LED on
    }
}
