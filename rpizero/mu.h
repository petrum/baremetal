#ifndef __MU_H__
#define __MU_H__

#include "gpio.h"

struct MU
{
    static void init(int addr);
public:
    static char getc();
    static void putc(char c);
public:
    static void write(const char* buffer);
    static void hexstring(unsigned int d);
private:
    static void send(char);
    static volatile unsigned int* mu_;
};

const int AUX_ENABLES     = 0x04 / 4;
const int AUX_MU_IO_REG   = 0x40 / 4;
const int AUX_MU_IER_REG  = 0x44 / 4;
const int AUX_MU_IIR_REG  = 0x48 / 4;
const int AUX_MU_LCR_REG  = 0x4C / 4;
const int AUX_MU_MCR_REG  = 0x50 / 4;
const int AUX_MU_LSR_REG  = 0x54 / 4;
const int AUX_MU_MSR_REG  = 0x58 / 4;
const int AUX_MU_SCRATCH  = 0x5C / 4;
const int AUX_MU_CNTL_REG = 0x60 / 4;
const int AUX_MU_STAT_REG = 0x64 / 4;
const int AUX_MU_BAUD_REG = 0x68 / 4;

inline void MU::init(int addr)
{
    mu_ = (unsigned int*)addr;
    
    mu_[AUX_ENABLES] = 1; // Auxiliary enables (1 == MU, 2 == SPI1, 4 == SPI2)
    mu_[AUX_MU_IER_REG] = 0; // Interrupt enable
    //mu_[AUX_MU_IIR_REG] = 0x0; // Interrupt identify

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

inline void MU::putc(char c)
{
    
    if (c == '\n' || c == '\r')
    {
        send('\n');
        send('\r');
    }
    else if (c == 0x7F)
    {
        send('\b');
    }
    else
    {
        send(c);
    }
}

inline void MU::send(char c)
{
    while (true)
    {
        if (mu_[AUX_MU_LSR_REG] & 0x20) // Line status
            break;
    }
    mu_[AUX_MU_IO_REG] = c;
}

inline char MU::getc()
{
    while (true)
    {
        if (mu_[AUX_MU_LSR_REG] & 0x01) // Line status
            break;
    }
    return mu_[AUX_MU_IO_REG] & 0xFF;
}

inline void MU::hexstring(unsigned int d)
{
    MU::send('0');
    MU::send('x');
    int rb = 32;
    while (true)
    {
        rb -= 4;
        char rc = (d >> rb) & 0xF;
        if (rc > 9)
            rc += ('A' - 10);
        else
            rc += '0';
        MU::send(rc);
        if (rb == 0)
            break;
    }
}

inline void MU::write(const char* buffer)
{
    for (; *buffer != 0; ++buffer)
    {
        putc(*buffer);
    }
}

#endif
