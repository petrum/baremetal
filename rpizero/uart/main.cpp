#include "../gpio.h"
#include "../misc.h"

#define GPPUD       0x94
#define GPPUDCLK0   0x98

#define AUX_ENABLES     0x15004
#define AUX_MU_IO_REG   0x15040
#define AUX_MU_IER_REG  0x15044
#define AUX_MU_IIR_REG  0x15048
#define AUX_MU_LCR_REG  0x1504C
#define AUX_MU_MCR_REG  0x15050
#define AUX_MU_LSR_REG  0x15054
#define AUX_MU_CNTL_REG 0x15060
#define AUX_MU_BAUD_REG 0x15068

static inline void delay(int32_t count)
{
  asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
               : : [count]"r"(count) : "cc");
}

void uart_putc(unsigned int c)
{
    while (1)
    {
        if (GPIO::gpio_[AUX_MU_LSR_REG] & 0x20)
            break;
    }
    GPIO::gpio_[AUX_MU_IO_REG, c];
}

void hexstrings(unsigned int d)
{
    unsigned int rb;
    unsigned int rc;

    rb = 32;
    while (1)
    {
        rb -= 4;
        rc = (d >> rb) & 0xF;
        if (rc > 9)
            rc += 0x37;
        else
            rc += 0x30;
        uart_putc(rc);
        if (rb == 0)
            break;
    }
    uart_putc(0x20);
}

void hexstring(unsigned int d)
{
    hexstrings(d);
    uart_putc(0x0D);
    uart_putc(0x0A);
}

volatile unsigned int* GPIO::gpio_;

int main(void) __attribute__((naked)); 
int main(void)
{
    enableBranchPrediction();
    enableL1Cache();

    GPIO::init(0x20200000);


    GPIO::gpio_[AUX_ENABLES] = 1;
    GPIO::gpio_[AUX_MU_IER_REG] = 0;
    GPIO::gpio_[AUX_MU_CNTL_REG] = 0;
    GPIO::gpio_[AUX_MU_LCR_REG] = 3;
    GPIO::gpio_[AUX_MU_MCR_REG] = 0;
    GPIO::gpio_[AUX_MU_IER_REG] = 0;
    GPIO::gpio_[AUX_MU_IIR_REG] = 0xC6;
    GPIO::gpio_[AUX_MU_BAUD_REG] = 270;

    GPIO::setMode(14, GPIO::Alt5);
    GPIO::setMode(15, GPIO::Alt5);
   
    GPIO::gpio_[GPPUD] = 0;
    for (ra = 0; ra < 150; ra++)
        delay(150);
    GPIO::gpio_[GPPUDCLK0] =  (1 << 14) | (1 << 15);
    for (ra = 0; ra < 150; ra++)
        delay(150);
    GPIO::gpio_[GPPUDCLK0] = 0;
    GPIO::gpio_[AUX_MU_CNTL_REG] = 3;

    hexstring(0x12345678);
    hexstring(earlypc);

    while (1)
    {
        while (1)
        {
            if (GPIO::gpio_[AUX_MU_LSR_REG] & 0x01)
                break;
        }
        unsined int ra = GPIO::gpio_[AUX_MU_IO_REG];
        while (1)
        {
            if (GPIO::gpio_[AUX_MU_LSR_REG] & 0x20)
                break;
        }
        GPIO::gpio_[AUX_MU_IO_REG] = ra;
    }

    return 0;


    ra = GPIO::gpio_[GPFSEL1);
    ra &= ~(7 << 12); //gpio14
    ra |= 2 << 12;    //alt5
    ra &= ~(7 << 15); //gpio15
    ra |= 2 << 15;    //alt5
    GPIO::gpio_[GPFSEL1, ra);
}
