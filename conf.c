/* 
 * File:   conf.c
 * Author: mtleising
 *
 * Created on March 2, 2015, 3:19 PM
 */

#include "conf.h"

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
