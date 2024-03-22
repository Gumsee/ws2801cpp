#pragma once
#include <stdint.h>
#include <string>
#include <linux/spi/spidev.h>

class SPI
{
private:
    std::string sSPIFileName;
    int iSPIfd;
    uint8_t iMode;
    uint8_t iBitsPerWord;
    uint32_t iSpeed;
    uint16_t iDelay;
    bool bActive;

public:
    SPI(std::string spidev);
    ~SPI();

    bool start();
    bool stop();
    int read(uint8_t* data, uint32_t len);  //RX
    int write(uint8_t* data, uint32_t len); //TX
    //int xfer(uint8_t *p_txbuffer, uint8_t p_txlen, uint8_t *p_rxbuffer, uint8_t p_rxlen);

    //Setter
    bool setSpeed(uint32_t speed);
    bool setMode(uint8_t mode);
    bool setBitsPerWord(uint8_t bits);
    
    //Getter
    uint32_t getSpeed();
    uint8_t getMode();
    uint8_t setBitsPerWord();
};
