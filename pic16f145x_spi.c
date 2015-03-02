
#include <xc.h>

//**************************************************************************************
// Send one byte
//**************************************************************************************
unsigned int spi(unsigned int mosi)
{
    unsigned int miso;

    PIR1bits.SSP1IF=0;          // Clear SSP interrupt bit
    SSPBUF = mosi;              // Write dummy data byte to the buffer to initiate transmission
    while(!SSPSTATbits.BF);     // Wait for interrupt flag to go high indicating transmission is complete
    miso = SSPBUF;          // Read the incoming data byte
    return (miso);
}
