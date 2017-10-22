#ifndef __MISC_H__
#define __MISC_H__

//https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=98904#p689471
inline void enableBranchPrediction()
{
    unsigned int nAuxControl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  1" : "=r" (nAuxControl));
    nAuxControl |= 1 << 11;
    asm volatile ("mcr p15, 0, %0, c1, c0,  1" : : "r" (nAuxControl));   // SMP bit must be set according to ARM TRM    
}

inline void enableL1Cache()
{
    unsigned int nControl;
    asm volatile ("mrc p15, 0, %0, c1, c0,  0" : "=r" (nControl));
    nControl |= 1 << 12;
    asm volatile ("mcr p15, 0, %0, c1, c0,  0" : : "r" (nControl) : "memory");    
}

inline void delay(int count)
{
    for (int i = 0; i < count; ++i)
    {
        asm volatile ("");
    }
    
    /*
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
                 : : [count]"r"(count) : "cc");
This generates some strange __delay_XX variable (10 - 90).
Example:

000181b0 R __data_start
00008098 t __delay_10
000080a4 t __delay_12
000080b0 t __delay_14
000080bc t __delay_16
000080c8 t __delay_18
000080d4 t __delay_20
//...
0000806c t __delay_90
000181b4 B __end__
    */
}

inline void shortDelay()
{
    delay(10000000);
}

inline void longDelay()
{
    for (int i = 0; i != 3; ++i)
        shortDelay();
}

#endif
