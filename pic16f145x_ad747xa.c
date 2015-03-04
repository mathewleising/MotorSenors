
#include "pic16f145x_ad747xa.h"

void ad747_init()
{
    CUR_CS = 1;
    VIB_CS = 1;
}

unsigned int adc_8()
{
    unsigned int data = 0x00;

    CUR_CS = 0;

    // OPCODE
    data = spi(0x00)<<4;
    data = data|(spi(0x00)>>4);

    CUR_CS = 1;

    return data;
}

void adc_12(unsigned int * mosi)
{
    VIB_CS = 0;

    // OPCODE
    mosi[0] = spi(0x00);
    mosi[1] = spi(0x00);

    VIB_CS = 1;
}
