/* 
 * File:   pic16f145x_ad747xa.h
 * Author: mtleising
 *
 * Created on March 4, 2015, 1:07 PM
 */

#ifndef PIC16F145X_AD747XA_H
#define	PIC16F145X_AD747XA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "pic16f145x_spi.h"
#include "conf.h"

void ad747_init(void);
unsigned int adc_8(void);
void adc_12(unsigned int * data);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC16F145X_AD747XA_H */

