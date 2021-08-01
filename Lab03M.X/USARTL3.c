/*
 * File:   USART.c
 * Author: Admin
 *
 * Created on 31 de julio de 2021, 07:07 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "USARTL3.h"
#define _XTAL_FREQ 8000000 

void UARTInit(const uint32_t baud_rate, const uint8_t BRGH) {

    if (BRGH == 0) {
        SPBRG = _XTAL_FREQ / (64 * baud_rate) - 1;
        TXSTAbits.BRGH = 0;
    } else {
        SPBRG = _XTAL_FREQ / (16 * baud_rate) - 1;
        TXSTAbits.BRGH = 1;
    }

    // TXSTA register
    TXSTAbits.TX9 = 0; // 8-bit transmission
    TXSTAbits.TXEN = 1; // Enable transmission
    TXSTAbits.SYNC = 0; // Asynchronous mode

    // RCSTA register
    RCSTAbits.SPEN = 1; // Enable serial port
    RCSTAbits.RX9 = 0; // 8-bit reception
    RCSTAbits.CREN = 1; // Enable continuous reception
    RCSTAbits.FERR = 0; // Disable framing error
    RCSTAbits.OERR = 0; // Disable overrun error

    // Set up direction of RX/TX pins
    USART_TRIS_RX = 1;
    USART_TRIS_TX = 0;
}


void UARTSendChar(const char c) {
    while (!TXIF); // Wait for buffer to be empty
    TXREG = c;
}


void UARTSendString(const char* str, const uint8_t max_length) {
    int i = 0;

    while (str[i] !=0){
        UARTSendChar(str[i]);
        i++;
        __delay_us(30);
    }
}


uint8_t UARTDataReady() {
    return PIR1bits.RCIF;
}


char UARTReadChar() {
    while (!UARTDataReady()); // Wait for data to be available
    return RCREG;
}


uint8_t UARTReadString(char *buf, uint8_t max_length) {
    uint8_t i = 0;
    char tmp = 1;
    for (i = 0; i < max_length - 1; i++) {
        tmp = UARTReadChar();
        // Stop reading if end of string is read
        if (tmp == '\0' || tmp == '\n' || tmp == '\r') {
            break;
        }
        buf[i] = tmp;
    }

    buf[i + 1] = '\0';

    return i;
}

