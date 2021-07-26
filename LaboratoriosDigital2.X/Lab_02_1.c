/*
 * File:   Lab_02.c
 * Author: Josue Salazar 
 *
 * Created on 24 de julio de 2021, 11:37 PM
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

#define _XTAL_FREQ 8000000 
#define _tmr0_value 217


//**********Variables***********
uint8_t canal_act = 0;
volatile uint8_t var_adc0 = 0;
volatile uint8_t var_adc1 = 0;
float cont_uart = 0;
char string_uart[10];
char valor_uart = 0;
char adc0[10];
char adc1[10];
float conv0 = 0;
float conv1 = 0;
 //**********Prototipos*********
 void config(void);

void main(void) {
    config();
  Lcd_Init();
   start_adc(2, 0, 0, 0); //Fosc/8, No ISR de ADC, Ref Vdd y Vcc, a la izquierda
    start_ch(0); //Habilita el pin del Puerto RB0.
    start_ch(1); //Habilita el pin del Puerto RB1.
    Select_ch(0); //Selecciona el canal e inicia la conversion.
    Lcd_Clear();
  while(1)
  {
      Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1:");
        Lcd_Set_Cursor(1, 8);
        Lcd_Write_String("S2:");
        Lcd_Set_Cursor(1, 15);
        Lcd_Write_String("S3:");
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
  

   
    Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(adc0);
        Lcd_Set_Cursor(2, 5);
        Lcd_Write_String("V");

        Lcd_Set_Cursor(2, 7);
        Lcd_Write_String(adc1);
        Lcd_Set_Cursor(2, 11);
        Lcd_Write_String("V");


    
     conv0 = 0;//se reinicia las cada ves que se inicia el proceso de enviar datos
     conv1 = 0;//tanto para la LCD como por UART.
        
        conv0 = (var_adc0 / (float) 255)*5; //Se consigue el porcentaje con respecto al valor 
       //maximo que un puerto puede tener, despues se multiplica por 5 para conocer el voltaje actual del puerto                                          
        convert(adc0, conv0, 2);//se convierte el valor actual a un valor ASCII.
        
        conv1 = (var_adc1 / (float) 255)*5; //misma logica que conv0
        convert(adc1, conv1, 2);
  }
    return;
}
void config(void) {
    //Configuracion de los puertos
    ANSEL   = 0X00;             //Colocamos RA0 como entrada analogica
    ANSELH  = 0X00;             //PORTB, el PORTC y PORTD como salidas
    
                                 //Colocamos RA0 Y RA1 como entradas y el resto del
    TRISC   = 0X00;             //PORTB, el PORTC y PORTD como salidas
    TRISD   = 0X00;
    TRISA   = 0X03;
    TRISE   = 0X00;
    
    PORTA   = 0X00;
    PORTC   = 0X00;
    PORTD   = 0X00;
    PORTE   = 0x00;
    
    //Configuracion del Oscilador
        config_osc(7);
    //Configuracion TMR0
//    config_tmr0(7);
//    TMR0 = _tmr0_value;
    
//    //Configuracion Interupciones
//    INTCONbits.GIE   = 1;       //Activamos las interupciones on change y del TMR0
//    INTCONbits.PEIE  = 1;
//    INTCONbits.T0IE  = 1;
//    INTCONbits.RBIE  = 1;
//    PIE1bits.ADIE    = 1;
//    
//    INTCONbits.T0IF  = 0;
//    INTCONbits.RBIF  = 0;
//    PIR1bits.ADIF    = 0;
//    
//     //Configuracion ADC
//    ADCON1bits.ADFM     = 0;    //Justificado a la izquierda
//    ADCON1bits.VCFG0    = 0;    //Colocamos los voltajes de ref como VSS y VDD
//    ADCON1bits.VCFG1    = 0;
//    
//    ADCON0bits.ADCS1    = 1;    //Reloj de conversion como FOSC/32
//    ADCON0bits.CHS      = 0;    //Chanel 0
//    __delay_ms(200);
//    ADCON0bits.ADON     = 1;    //Encendemos el ADC
//    __delay_ms(200);
//   
//    
}