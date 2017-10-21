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
