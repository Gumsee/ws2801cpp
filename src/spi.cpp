#include "spi.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>


SPI::SPI(std::string spidev)
{
    sSPIFileName = spidev;
    bActive = false;
}

SPI::~SPI()
{
    stop();
}

bool SPI::start()
{
    if (bActive)
       return true;

    if (sSPIFileName.empty())
       return false;

    iSPIfd = open(sSPIFileName.c_str(), O_RDWR);
    if (iSPIfd < 0)
        return false;

    if(ioctl(iSPIfd, SPI_IOC_WR_MODE, &iMode) < 0
    || ioctl(iSPIfd, SPI_IOC_RD_MODE, &iMode) < 0
    || ioctl(iSPIfd, SPI_IOC_WR_BITS_PER_WORD, &iBitsPerWord) < 0
    || ioctl(iSPIfd, SPI_IOC_RD_BITS_PER_WORD, &iBitsPerWord) < 0
    || ioctl(iSPIfd, SPI_IOC_WR_MAX_SPEED_HZ, &iSpeed) < 0
    || ioctl(iSPIfd, SPI_IOC_RD_MAX_SPEED_HZ, &iSpeed) < 0) {
        close(iSPIfd);
        return false;
    }

    bActive = true;
    return true;
}

bool SPI::stop()
{
    if(bActive)
        return close(iSPIfd);
    return true;
}

int SPI::read(uint8_t* data, uint32_t len)
{
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    spi_message[0].rx_buf = (unsigned long)data;
    spi_message[0].len = len;

    return ioctl(iSPIfd, SPI_IOC_MESSAGE(1), spi_message);
}

int SPI::write(uint8_t* data, uint32_t len)
{
    struct spi_ioc_transfer spi_message[1];
    memset(spi_message, 0, sizeof(spi_message));
    spi_message[0].tx_buf = (unsigned long)data;
    spi_message[0].len = len;

    return ioctl(iSPIfd, SPI_IOC_MESSAGE(1), spi_message);
}

//int xfer(uint8_t *p_txbuffer, uint8_t p_txlen, uint8_t *p_rxbuffer, uint8_t p_rxlen);




//
//Setter
//
bool SPI::setSpeed(uint32_t speed)
{
    if(ioctl(iSPIfd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0
    || ioctl(iSPIfd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0)
        return false;

    iSpeed = speed;
    return true;
}

bool SPI::setMode(uint8_t mode)
{
    if(ioctl(iSPIfd, SPI_IOC_WR_MODE, &mode) < 0
    || ioctl(iSPIfd, SPI_IOC_RD_MODE, &mode) < 0)
        return false;

    iMode = mode;
    return true;
}

bool SPI::setBitsPerWord(uint8_t bits)
{
    /* Set bits per word*/
    if(ioctl(iSPIfd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0
    || ioctl(iSPIfd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
        return false;

    iBitsPerWord = bits;
    return true;
}



//
//Getter
//
uint32_t SPI::getSpeed()      { return iSpeed; }
uint8_t SPI::getMode()        { return iMode; }
uint8_t SPI::setBitsPerWord() { return iBitsPerWord; }
