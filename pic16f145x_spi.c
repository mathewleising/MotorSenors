
#include "pic16f145x_spi.h"

void spi_config()
{
    //**********************************************************************************
    // Setup SPI:
    //**********************************************************************************
    // Note: current version of the XC8 compiler (v1.12)  uses the designator "SSPCON" for the
    // first MSSP control register, however, future versions of the compiler may use
    // "SSPCON1" or another variant. If you get errors for this register below
    // this is probably the reason.
    //**********************************************************************************

    SSPCONbits.SSPM = 0x00;       // SPI Master mode, clock = Fosc/16 (1 Mhz)
    SSPCONbits.CKP = 0x00;        // Idle state for clock is low
    SSPSTATbits.CKE = 0x01;       // Transmit occurs on transition from active to idle clock state
    SSPSTATbits.SMP = 0x00;       // Data is sampled at middle of data output time
    SSPCONbits.SSPEN = 0x01;      // Enable SPI Port
}


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
