/* 
 * File:   conf.c
 * Author: mtleising
 *
 * Created on March 2, 2015, 3:19 PM
 */

#include <xc.h>

void osc_config()
{
    // Set up oscillator control register for 48MHz - Pg. 73
    // TODO: change to external osc when ready
    OSCCONbits.IRCF = 0x0F;
    OSCCONbits.SCS = 0x00;
    OSCCONbits.SPLLEN = 0x01;
    OSCCONbits.SPLLMULT = 0x01;

    OSCTUNEbits.TUN = 0xFF;
}

void port_config()
{
    // Port Assignents
    // SPI
    TRISCbits.TRISC0 = 0; // RC3 = SCK output SEE
    TRISCbits.TRISC1 = 1; // RC4 = SDI input from SEE
    TRISCbits.TRISC2 = 0; // RC5 = SDO output to SEE

    // ADCs
    TRISCbits.TRISC4 = 0; // Current
    TRISCbits.TRISC5 = 0; // Vibration

    // WIZ5200
    TRISCbits.TRISC3 = 0; // CS
    TRISAbits.TRISA4 = 0; // RST
    TRISAbits.TRISA5 = 1; // INTR
}

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

