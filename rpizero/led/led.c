//unsigned int* gpio = (unsigned int*)0x20200000; // this lines makes the binary file huge!
unsigned int* gpio;
unsigned int tim;

int main(void)
{
    gpio = (unsigned int*)0x20200000;
    while (1)
    {
        for(tim = 0; tim < 5000000; tim++)
            ;
        gpio[8] = (1 << 15);
        for(tim = 0; tim < 5000000; tim++)
            ;
        gpio[11] = (1 << 15);
    }
}
