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
    dot(); dot(); dot(); line(); line(); line(); dot(); dot(); dot();
}

int main(void)
{
    gpio = (unsigned int*)0x20200000;
    while (1)
    {
        sos();
        longDelay();
        longDelay();
    }
}
