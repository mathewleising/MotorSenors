/* 
 * File:   main.c
 * Author: mathewleising
 *
 * Created on January 12, 2015, 2:31 PM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pic16f145x_spi.h"
#include "pic16f145x_wiznet.h"
#include "conf.h"

// PIC16F1454 Configuration Bit Settings
// CONFIG1
#pragma config FOSC = INTOSC // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = ON  // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (NO CPU system divide)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED // PLL Enable Bit (3x or 4x PLL Disabled)
#pragma config STVREN = ON // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF // Low-Voltage Programming Enable (Low-voltage programming enabled)



void config()
{
    // Set up oscillator control register for 48MHz - Pg. 73
    // TODO: change to external osc when ready
    OSCCONbits.IRCF = 0x0F;
    OSCCONbits.SCS = 0x00;
    OSCCONbits.SPLLEN = 0x01;
    OSCCONbits.SPLLMULT = 0x01;

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

    // Set up spi
    spi_conf_t spi_conf;
    spi_conf.CKE_bits = 0x00;
    spi_conf.CKP_bits = 0x00;
    spi_conf.SMP_bits = 0x01;
    spi_conf.SSPEN_bits = 0x00;
    spi_conf.SSPM_bits = 0x01;
    spi_setup(spi_conf);

    // Setup Wiz5200
    wiz_conf_t wiz_conf;

    for(int i = 0; i<REG_GATEWAY_IP_LENGTH; i++)
        wiz_conf.gateway[i] = 0x00;

    wiz_conf.ip[0] = 0xA9;
    wiz_conf.ip[1] = 0x80;
    wiz_conf.ip[2] = 0x80;
    wiz_conf.ip[3] = 0x82;

    wiz_conf.mac[0] = 0x54;
    wiz_conf.mac[1] = 0x52;
    wiz_conf.mac[2] = 0x00;
    wiz_conf.mac[3] = 0x00;
    wiz_conf.mac[4] = 0xF8;
    wiz_conf.mac[5] = 0x01;

    wiz_conf.subnet[0] = 0xFF;
    wiz_conf.subnet[1] = 0x00;
    wiz_conf.subnet[2] = 0x00;
    wiz_conf.subnet[3] = 0x00;

    wiz_conf.source_ip[0] = 0xA9;
    wiz_conf.source_ip[1] = 0x80;
    wiz_conf.source_ip[2] = 0x80;
    wiz_conf.source_ip[3] = 0x81;

    wiz_conf.source_port[0] = 0x13;
    wiz_conf.source_port[1] = 0x88;
    
    wiz_init(wiz_conf);
}

int main(int argc, char** argv)
{
    config();

    while (1) {
        WIZ_CS = 0;
        spi(0x55);
        WIZ_CS = 1;
        __delay_us(10);
    }

    return (EXIT_SUCCESS);
}

