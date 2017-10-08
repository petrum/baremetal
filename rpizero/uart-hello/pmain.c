extern void PUT32(unsigned int, unsigned int);
extern unsigned int GET32(unsigned int);

static unsigned int PBASE;

#define GPFSEL1         (PBASE + 0x00200004)
#define GPSET0          (PBASE + 0x0020001C)
#define GPCLR0          (PBASE + 0x00200028)

#define AUX_ENABLES     (PBASE + 0x00215004)
#define AUX_MU_IO_REG   (PBASE + 0x00215040)
#define AUX_MU_IER_REG  (PBASE + 0x00215044)
#define AUX_MU_IIR_REG  (PBASE + 0x00215048)
#define AUX_MU_LCR_REG  (PBASE + 0x0021504C)
#define AUX_MU_MCR_REG  (PBASE + 0x00215050)
#define AUX_MU_LSR_REG  (PBASE + 0x00215054)
#define AUX_MU_MSR_REG  (PBASE + 0x00215058)
#define AUX_MU_SCRATCH  (PBASE + 0x0021505C)
#define AUX_MU_CNTL_REG (PBASE + 0x00215060)
#define AUX_MU_STAT_REG (PBASE + 0x00215064)
#define AUX_MU_BAUD_REG (PBASE + 0x00215068)

static void uart_init ( void )
{
    unsigned int ra;

    PUT32(AUX_ENABLES, 1);
    PUT32(AUX_MU_IER_REG, 0);
    PUT32(AUX_MU_CNTL_REG, 0);
    PUT32(AUX_MU_LCR_REG, 3);
    PUT32(AUX_MU_MCR_REG, 0);
    PUT32(AUX_MU_IER_REG, 0);
    PUT32(AUX_MU_IIR_REG, 0xC6);
    PUT32(AUX_MU_BAUD_REG, 270);
    ra = GET32(GPFSEL1);
    ra &= ~(7 << 12); //gpio14
    ra |= 2 << 12;    //alt5
    ra &= ~(7 << 15); //gpio15
    ra |= 2 << 15;    //alt5
    PUT32(GPFSEL1, ra);
    PUT32(AUX_MU_CNTL_REG, 3);
}

static void uart_send(char c)
{
    while (1)
    {
        if (GET32(AUX_MU_LSR_REG) & 0x20) 
            break;
    }
    PUT32(AUX_MU_IO_REG, c);
}

void send_string(const char *s)
{
    while(*s)
    {
        uart_send(*s++);
    }
}

int pmain()
{
    PBASE = 0x20000000;
    uart_init();
    send_string("Hello world!\n");
    return 0;
}

