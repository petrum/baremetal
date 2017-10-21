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

int main()
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);
    MU::init(0x20215000);
   
    MU::write("Hello world!\n\r");
    hexstring(32);
    
    while (true)
    {
        MU::send(MU::recv());
    }
    return 0;
}
