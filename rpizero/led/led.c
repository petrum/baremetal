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
    gpio[8] = (1 << 15); // LED off
}

void on()
{
    gpio[11] = (1 << 15); // LED on
}

void sos()
{
    on(); shortDelay(); off(); shortDelay(); 
    on(); shortDelay(); off(); shortDelay(); 
    on(); shortDelay(); off(); longDelay();
    
    on(); longDelay(); off(); shortDelay(); 
    on(); longDelay(); off(); shortDelay(); 
    on(); longDelay(); off(); longDelay();
    
    on(); shortDelay(); off(); shortDelay(); 
    on(); shortDelay(); off(); shortDelay(); 
    on(); shortDelay(); off(); longDelay();    
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
