
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#pragma config FOSC = INTRC_NOCLKOUT
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

//COnversion ADC 
void convert(char *data,float a, int place);
void start_adc(uint8_t frec, uint8_t isr, uint8_t Vref, uint8_t justRL);
void Select_ch(uint8_t channel);
void start_ch(uint8_t channel);


#endif	/* XC_HEADER_TEMPLATE_H */

