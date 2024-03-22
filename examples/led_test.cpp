#include <iostream>
#include <ws2801.h>

#define NUM_LEDS 100

int main(char** argv, int argc)
{
    std::cout << "Testing LEDs" << std::endl;
    WS2801* pWS2801 = new WS2801("/dev/spidev1.0", WS2801_RGB, NUM_LEDS);


    //Write "purple" (super fast switch between red & blue)
    while(true)
    {
        for(int i = 0; i < NUM_LEDS; i++)
        {
            pWS2801->setPixel(i, WS2801::pixel(0,0,255));
        }
        pWS2801->show();
        for(int i = 0; i < NUM_LEDS; i++)
        {
            pWS2801->setPixel(i, WS2801::pixel(255,0,0));
        }
        pWS2801->show();
    }

    delete pWS2801;
    return 0;
}
