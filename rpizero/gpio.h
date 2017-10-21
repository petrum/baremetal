#ifndef __GPIO_H__
#define __GPIO_H__

struct GPIO
{
    enum Mode {In, Out, Alt5, Alt4, Alt0, Alt1, Alt2, Alt3};
    enum PUD {PullOff, PullDown, PullUp};
    static void init(int addr);
    static Mode getMode(int i);
    static Mode setMode(int i, Mode m);
    static void setPUD(int i, PUD ud);
    static void on(int i);
    static void off(int i);
    static void delay(int count);
private:
    static volatile unsigned int* gpio_;
};

inline void GPIO::init(int addr)
{
    gpio_ = (unsigned int*)addr;
}

inline GPIO::Mode GPIO::getMode(int i)
{
    int wIndex = i / 10;
    int bIndex = (i % 10) * 3;
    return (Mode)((gpio_[wIndex] & (7 << bIndex)) >> bIndex);
}

inline GPIO::Mode GPIO::setMode(int i, Mode m)
{
    GPIO::Mode old = GPIO::getMode(i);
    // i == 0 - 53
    // https://raspberrypi.stackexchange.com/questions/39252/on-board-led-connection-to-gpio
    // "the power LED (red) is connected to GPIO 35 (not present on the Pi Zero)"
    // "the activity LED (green) is connected to GPIO 47"
    
    // http://www.susa.net/wordpress/2012/07/raspberry-pi-gpfsel-gpio-and-pads-status-viewer/
    // FSEL47 (GPFSEL4[21-23]) = 0 (GPIO In - [Low])
    // In == 0, Out == 1, ALT0-ALT5 from 2 to 7 (total of 8, of three available bits)
    int wIndex = i / 10;
    int bIndex = (i % 10) * 3;
    gpio_[wIndex] = (gpio_[wIndex] & ~(7 << bIndex)) | m << bIndex;
    // FSEL35 (GPFSEL3[15-17]) = 0 (GPIO In - [Low]): 
    return old;
}

inline void GPIO::on(int i)
{
    // pag. 90 in the BCM2835 ARM Peripherals doc
    if (i < 32)
        gpio_[10] = 1 << i;
    else
        gpio_[11] = 1 << (i - 32);
}

inline void GPIO::off(int i)
{
    if (i < 32)
        gpio_[7] = 1 << i;
    else
        gpio_[8] = 1 << (i - 32);
}

inline void GPIO::setPUD(int i, PUD pud)
{
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    gpio_[0x94] = pud;
    delay(150);
    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    int PUDCLK = i < 32 ? 0x98 : 0x9C;
    gpio_[PUDCLK] = 1 << i;
    delay(150);
    // Write 0 to GPPUDCLK0 to make it take effect.
    gpio_[PUDCLK] = 0;
}

inline void GPIO::delay(int count)
{
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
                 : : [count]"r"(count) : "cc");
}


#endif
