
#include "pic16f145x_spi.h"

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


void spi_setup(spi_conf_t conf)
{
    //**********************************************************************************
    // Setup SPI:
    //**********************************************************************************
    // Note: current version of the XC8 compiler (v1.12)  uses the designator "SSPCON" for the
    // first MSSP control register, however, future versions of the compiler may use
    // "SSPCON1" or another variant. If you get errors for this register below
    // this is probably the reason.
    //**********************************************************************************

    SSPCONbits.SSPM = conf.SSPM_bits;       // SPI Master mode, clock = Fosc/16 (1 Mhz)
    SSPCONbits.CKP = conf.CKP_bits;           // Idle state for clock is low
    SSPSTATbits.CKE = conf.CKE_bits;          // Transmit occurs on transition from active to idle clock state
    SSPSTATbits.SMP = conf.SMP_bits;          // Data is sampled at middle of data output time
    SSPCONbits.SSPEN = conf.SSPEN_bits;      // Enable SPI Port
}