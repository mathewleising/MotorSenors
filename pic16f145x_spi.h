/* 
 * File:   pic16f145x_spi.h
 * Author: mathewleising
 *
 * Created on January 14, 2015, 11:01 AM
 */

#ifndef PIC16F145X_SPI_H
#define	PIC16F145X_SPI_H

#include <xc.h>


typedef struct spi_conf_t
{
    unsigned int SSPM_bits;
    unsigned int CKP_bits;
    unsigned int CKE_bits;
    unsigned int SMP_bits;
    unsigned int SSPEN_bits;

} spi_conf_t;

void spi_setup(spi_conf_t conf);
unsigned int spi(unsigned int mosi);



#endif	/* PIC16F145X_SPI_H */

