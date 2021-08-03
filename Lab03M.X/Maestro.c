/*
 * File:   Maestro.c
 * Author: Admin
 *
 * Created on 31 de julio de 2021, 02:11 PM
 */


#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibreriasL3.h"
#include "ADCL3.h"
#include "USARTL3.h"



#define _XTAL_FREQ 8000000 
#define _tmr0_value 217

//**********Variables***********
//uint8_t canal_act = 0;
//volatile uint8_t var_adc0 = 0;
//volatile uint8_t var_adc1 = 0;
char adc0;
char adc1;
float conv0 = 0;
float conv1 = 0;
//uint8_t contador;
uint8_t sensor1;
uint8_t sensor2;

 //**********Prototipos*********
 void config(void);
 
void main(void) {
    
    config();
    while(1){
        PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(1);
       PORTB = spiRead();
//       PORTB = sensor1;
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(2);
       PORTD = spiRead();
//       PORTD = sensor2;
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect
       UARTInit(9600,1);
       conv0 = (PORTB / (float) 255)*5;
       conv1 = (PORTD / (float) 255)*5;
       convert(adc0, conv0, 2);
       convert(adc1, conv1, 2);
        UARTInit(9600, 1);
        UARTSendString("|", 3);
        UARTSendString("S1", 6);
        UARTSendString(":", 3);
        UARTSendString(" ", 3);
        UARTSendString(adc0, 6);
        UARTSendString("V", 3);
        UARTSendString(",", 3);
        UARTSendString(" ", 3);
        
        UARTSendString("|", 3);
        UARTSendString("S2", 6);
        UARTSendString(":", 3);
        UARTSendString(" ", 3);
        UARTSendString(adc1, 6);
        UARTSendString("V", 3);
        UARTSendString(",", 3);
        UARTSendString(" ", 3);
       
    }
    return;
}

void config(void){
    ANSEL   = 0X00;             //Colocamos RA0 como entrada analogica
    ANSELH  = 0X00;             //PORTB, el PORTC y PORTD como salidas
    
                                 //Colocamos RA0 Y RA1 como entradas y el resto del
                //PORTB Como salidas
    TRISB = 0X00;
    TRISD = 0x00;
//    TRISC2 = 0;
        
    PORTB = 0X00;
    PORTD = 0X00;
    
    PORTCbits.RC2 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    //Configuracion del Oscilador
   config_osc(7);
   
   
   return;
}
