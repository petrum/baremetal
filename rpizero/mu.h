#ifndef __MU_H__
#define __MU_H__

struct MU
{
    static void init(int addr);
    static unsigned int recv();
    static void send(unsigned int);
private:
    static volatile unsigned int* mu_;
};

inline void MU::init(int addr)
{
    mu_ = (unsigned int*)addr;
    mu_[0x04] = 1; // Auxiliary enables
    mu_[0x44] = 0; // Interrup enable
    mu_[0x60] = 0; // Extra control
    mu_[0x4C] = 3; // Line control
    mu_[0x50] = 0; // Modem control
    mu_[0x44] = 0; // Interrup enable    
    mu_[0x48] = 0xC6; // Interrup identify
    mu_[0x68] = 270; // Baudrate    

    GPIO::setMode(14, GPIO::Alt5);
    GPIO::setMode(15, GPIO::Alt5);
    GPIO::setPUD(14, GPIO::PullOff);
    GPIO::setPUD(15, GPIO::PullOff);

    mu_[0x60] = 3;
}

inline void MU::send(unsigned int c)
{
    while (true)
    {
        if (mu_[0x54] & 0x20) // Line status
            break;
    }
    mu_[0x40] = c;
}

inline unsigned int MU::recv()
{
    while (true)
    {
        if (mu_[0x54] & 0x01) // Line status
            break;
    }
    return mu_[0x40] & 0xFF;
}

#endif
