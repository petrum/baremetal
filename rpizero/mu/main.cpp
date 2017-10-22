#include "../gpio.h"
#include "../misc.h"
#include "../mu.h"

volatile unsigned int* MU::mu_;
volatile unsigned int* GPIO::gpio_;
/*
$> arm-none-eabi-nm mu.elf 
//...
00018588 B _end
00080000 N _stack
00008000 T main  <=== the first non-inline function defined in the main.cpp compilation unit!
*/

int main(int r0, int r1, int atags)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);
    MU::init(0x20215000);
   
    MU::write("Hello world!\n");
    MU::hexstring(32);
    
    for (;;)
    {
        MU::putc(MU::getc());
    }
    return 0;
}
