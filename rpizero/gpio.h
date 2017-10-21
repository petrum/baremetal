#ifndef __GPIO_H__
#define __GPIO_H__

struct GPIO
{
    enum Mode {In, Out, Alt5, Alt4, Alt0, Alt1, Alt2, Alt3};
    static void init(int addr);
    static Mode getMode(int i);
    static Mode setMode(int i, Mode m);
    static void on(int i);
    static void off(int i);
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

void GPIO::on(int i)
{
    // pag. 90 in the BCM2835 ARM Peripherals doc
    if (i < 32)
        gpio_[10] = 1 << i;
    else
        gpio_[11] = 1 << (i - 32);
}

void GPIO::off(int i)
{
    if (i < 32)
        gpio_[7] = 1 << i;
    else
        gpio_[8] = 1 << (i - 32);
}

#endif
