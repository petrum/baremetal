#include "../gpio.h"
#include "../misc.h"
#include "../mu.h"

void hexstrings(unsigned int d)
{
    unsigned int rb;
    unsigned int rc;

    rb = 32;
    while (true)
    {
        rb -= 4;
        rc = (d >> rb) & 0xF;
        if (rc > 9)
            rc += 0x37;
        else
            rc += 0x30;
        MU::send(rc);
        if (rb == 0)
            break;
    }
    MU::send(0x20);
}

void hexstring(unsigned int d)
{
    hexstrings(d);
    MU::send(0x0D);
    MU::send(0x0A);
}

volatile unsigned int* MU::mu_;
volatile unsigned int* GPIO::gpio_;

int main(void) __attribute__((naked)); 
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);
    MU::init(0x20215000);
    
    hexstring(0x12345678);
    while (true)
    {
        MU::send(MU::recv());
    }
    return 0;
}
