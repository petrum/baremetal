#ifndef __GPIO_H__
#define __GPIO_H__

struct GPIO
{
    enum Mode {In, Out, ALT0, ALT1, ALT2, ALT3, ALT4, ALT5};
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
}

inline GPIO::Mode GPIO::setMode(int i, Mode m)
{
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
}

void GPIO::on(int i)
{
    gpio_[11] = 1 << (47 - 32);
}

void GPIO::off(int i)
{
    // the activity LED (green) is connected to GPIO 47
    gpio_[8] = 1 << (47 - 32);
}

#endif

