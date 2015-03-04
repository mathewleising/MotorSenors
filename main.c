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
#include "pic16f145x_ad747xa.h"
#include "pic16f145x_wiznet.h"
#include "conf.h"

// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = HS    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (NO CPU system divide)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

unsigned int gateway[REG_GATEWAY_IP_LENGTH] = {0x00,0x00,0x00,0x00};
unsigned int mac[REG_SOURCE_ADDR_MAC_LENGTH] = {0x54,0x52,0x00,0x00,0xF8,0x01};
unsigned int ip[REG_SOURCE_ADDR_IP_LENGTH] = {0xA9,0x80,0x80,0x82};
unsigned int subnet[REG_SUBNET_MASK_IP_LENGTH] = {0xFF,0x00,0x00,0x00};
unsigned int source_ip[REG_SOURCE_ADDR_IP_LENGTH] = {0xA9,0x80,0x80,0x81};
unsigned int source_port[PORT_LENGTH] = {0x13,0x88};

void config()
{
    port_config();

    spi_config();

    ad747_init();

    wiz_init();
}

int main(int argc, char** argv)
{
    config();

    while (1) {
        spi(OSCSTAT);
        __delay_us(10);
        //config();
        __delay_us(10);
    }

    return (EXIT_SUCCESS);
}
