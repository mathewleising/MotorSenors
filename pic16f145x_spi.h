/* 
 * File:   pic16f145x_spi.h
 * Author: mathewleising
 *
 * Created on January 14, 2015, 11:01 AM
 */

#ifndef PIC16F145X_SPI_H
#define	PIC16F145X_SPI_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

void spi_config(void);
unsigned int spi(unsigned int mosi);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC16F145X_SPI_H */

