/* 
 * File:   conf.h
 * Author: mathewleising
 *
 * Created on February 4, 2015, 3:39 PM
 */

#ifndef CONF_H
#define	CONF_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

// Definitions
#define _XTAL_FREQ  48000000        // this is used by the __delay_ms(xx) and __delay_us(xx) functions
#define CUR_CS      LATCbits.LATC4	// Chip Select Pin on Serial EEPROM
#define VIB_CS      LATCbits.LATC5	// Write Protect Pin on Serial EEPROM
#define WIZ_CS      LATCbits.LATC3	// Write Protect Pin on Serial EEPROM
#define WIZ_RST     LATAbits.LATA4	// Write Protect Pin on Serial EEPROM
#define WIZ_INTR    LATAbits.LATA5	// Write Protect Pin on Serial EEPROM

void port_config(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CONF_H */

