/*
 * File:   Lab_03E.c
 * Author: Admin
 *
 * Created on 31 de julio de 2021, 01:03 PM
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
#include "Librerias.h"
#include "ADC.h"
#include "LCD.h"
#include "USART.h"

#define _XTAL_FREQ 8000000 
#define _tmr0_value 217

//**********Variables***********
uint8_t canal_act = 0;
volatile uint8_t var_adc0 = 0;
volatile uint8_t var_adc1 = 0;
char adc0[10];
char adc1[10];
float conv0 = 0;
float conv1 = 0;

 //**********Prototipos*********
 void configE(void);

void main(void) {
    configE();
    start_adc(2, 1, 0, 0); //Fosc/8, No ISR de ADC, Ref Vdd y Vcc, a la izquierda
    start_ch(0); //Habilita el pin del Puerto RA0.
    start_ch(1); //Habilita el pin del Puerto RA1.
    Select_ch(0); //Selecciona el canal e inicia la conversion.
    
    UARTInit(9600, 1);
     while (1) {
         if (PIR1bits.ADIF == 1) {
            if (canal_act == 0) {
                var_adc0 = ADRESH; //se guarda el valor convertido en la variable
                Select_ch(0);
                canal_act++;
                
            } else {
                var_adc1 = ADRESH; //se guarda el valor convertido en la variable
                Select_ch(1);
                canal_act--;
                
            }
            PIR1bits.ADIF = 0;
        }
         conv0 = 0;
        //-----------------------------Sensor 1---------------------------------
        conv0 = (var_adc0 / (float) 255)*5;
        convert(adc0, conv0, 2);//se convierte el valor actual a un valor ASCIIv.
        PORTC = conv0;
          //-----------------------------Sensor 2---------------------------------
        conv1 = (var_adc1 / (float) 255)*5; //misma logica que conv0
        convert(adc1, conv1, 2);
        PORTD = conv1;
         
     }
    return;
}
void configE(void){
    ANSEL   = 0X00;             //Colocamos RA0 como entrada analogica
    ANSELH  = 0X00;             //PORTB, el PORTC y PORTD como salidas
    
    TRISA = 0X03;                    //Colocamos RA0 Y RA1 como entradas y el resto del
                    
    TRISB = 0X00; //PORTB Como salidas
    
    TRISC = 0X00;
    TRISD = 0X00;
    
    PORTA = 0X00;
    PORTB = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;
    
    //Configuracion del Oscilador
        config_osc(7);
}