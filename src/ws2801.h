#pragma once
#include "spi.h"
#include <string>

#define WS2801_RGB 0
#define WS2801_GRB 1


class WS2801
{
public:
    struct pixel
    {
        pixel(uint8_t r, uint8_t g, uint8_t b)
            : r(r), g(g), b(b) {}
        uint8_t r, g, b;
    };
private:
    SPI* pSPI;
    unsigned int iNumLeds;
    pixel* aPixels;

public:
    WS2801(std::string spidev, uint8_t ledorder, unsigned int numleds);
    ~WS2801();

    void setPixel(unsigned int index, const pixel& pix);
    pixel getPixel(unsigned int index);

    void show();
};
