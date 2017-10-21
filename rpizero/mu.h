#ifndef __MU_H__
#define __MU_H__

#include "gpio.h"

struct MU
{
    static void init(int addr);
    static unsigned int recv();
    static void send(unsigned int);
private:
    static volatile unsigned int* mu_;
};

#define AUX_ENABLES     (0x04 / 4)
#define AUX_MU_IO_REG   (0x40 / 4)
#define AUX_MU_IER_REG  (0x44 / 4)
#define AUX_MU_IIR_REG  (0x48 / 4)
#define AUX_MU_LCR_REG  (0x4C / 4)
#define AUX_MU_MCR_REG  (0x50 / 4)
#define AUX_MU_LSR_REG  (0x54 / 4)
#define AUX_MU_MSR_REG  (0x58 / 4)
#define AUX_MU_SCRATCH  (0x5C / 4)
#define AUX_MU_CNTL_REG (0x60 / 4)
#define AUX_MU_STAT_REG (0x64 / 4)
#define AUX_MU_BAUD_REG (0x68 / 4)

inline void MU::init(int addr)
{
    mu_ = (unsigned int*)addr;
    mu_[AUX_ENABLES] = 1; // Auxiliary enables (1 == MU, 2 == SPI1, 4 == SPI2)
    mu_[AUX_MU_IER_REG] = 0; // Interrupt enable
    mu_[AUX_MU_CNTL_REG] = 0; // Extra control
    mu_[AUX_MU_LCR_REG] = 3; // Line control
    mu_[AUX_MU_MCR_REG] = 0; // Modem control
    mu_[AUX_MU_IER_REG] = 0; // Interrupt enable    
    mu_[AUX_MU_IIR_REG] = 0xC6; // Interrupt identify
    mu_[AUX_MU_BAUD_REG] = 270; // Baudrate    

    GPIO::setMode(14, GPIO::Alt5);
    GPIO::setMode(15, GPIO::Alt5);
    GPIO::setPUD(14, GPIO::PullOff);
    GPIO::setPUD(15, GPIO::PullOff);

    mu_[AUX_MU_CNTL_REG] = 3; // Extra control
}

inline void MU::send(unsigned int c)
{
    while (true)
    {
        if (mu_[AUX_MU_LSR_REG] & 0x20) // Line status
            break;
    }
    dot();
    mu_[AUX_MU_IO_REG] = c;
}

inline unsigned int MU::recv()
{
    while (true)
    {
        if (mu_[AUX_MU_LSR_REG] & 0x01) // Line status
            break;
    }
    line();
    return mu_[AUX_MU_IO_REG] & 0xFF;
}

#endif
