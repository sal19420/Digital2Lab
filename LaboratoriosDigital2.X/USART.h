
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_H
#define	USART_H
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ  8000000

// Definimos pines 
#define USART_TRIS_RX  TRISCbits.TRISC7
#define USART_TRIS_TX  TRISCbits.TRISC6


void UARTInit(const uint32_t baud_rate, const uint8_t BRGH);
void UARTSendChar(const char c);     //mandamos el dato 
void UARTSendString(const char* str, const uint8_t max_length);
uint8_t UARTDataReady();    
char UARTReadChar();
uint8_t UARTReadString(char *buf, uint8_t max_length);

#endif	/* XC_HEADER_TEMPLATE_H */

