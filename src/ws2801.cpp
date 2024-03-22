#include "ws2801.h"
#include <iostream>
#include <chrono>
#include <thread>

WS2801::WS2801(std::string spidev, uint8_t ledorder, unsigned int numleds)
{
    pSPI = new SPI(spidev);
    if(!pSPI->start())
        std::cerr << "Failed to start SPI device" << std::endl;

    pSPI->setMode(SPI_MODE_0);
    pSPI->setBitsPerWord(24);
    pSPI->setSpeed(1000000);

    iNumLeds = numleds;

    aPixels = (pixel*)malloc(iNumLeds * sizeof(pixel));
}

WS2801::~WS2801()
{
    free(aPixels);
    delete pSPI;
}
    
void WS2801::setPixel(unsigned int index, const WS2801::pixel& pix)
{
    if(index >= iNumLeds)
        return;

    aPixels[index] = pix;
}

WS2801::pixel WS2801::getPixel(unsigned int index)
{
    if(index >= iNumLeds)
    {
        std::cerr << "Getting pixel out of range" << std::endl;
        return pixel(0,0,0);
    }

    return aPixels[index];
}

void WS2801::show()
{
    pSPI->write(&aPixels[0].r, iNumLeds * sizeof(pixel));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
