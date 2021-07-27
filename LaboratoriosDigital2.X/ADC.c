/*
 * File:   ADC.c
 * Author: Admin
 *
 * Created on 26 de julio de 2021, 10:44 AM
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000 
#include "ADC.h"
// Conversion de ADC 
void convert(char *data,float a, int place) //definition
{
     int temp=a;
     float x=0.0;
     int digits=0;
     int i=0,mu=1;
     int j=0;
     if(a<0)
     {
            a=a*-1;
            data[i]='-';
            i++;
      }
     //exponent component
     while(temp!=0)
     {
         temp=temp/10;
         digits++;          
     }
     while(digits!=0)
     {
         if(digits==1)mu=1;
         else  for(j=2;j<=digits;j++)mu=mu*10;
         
         x=a/mu;
         a=a-((int)x*mu);
         data[i]=0x30+((int)x);
         i++;
         digits--;
         mu=1;
     }
     //mantissa component
     data[i]='.';
     i++;
     digits=0;
     for(j=1;j<=place;j++)mu=mu*10;
     x=(a-(int)a)*mu; //shift places
     a=x;
     temp=a;
     x=0.0;
     mu=1;
     digits=place;
     while(digits!=0)
     {
         if(digits==1)mu=1;
         else  for(j=2;j<=digits;j++)mu=mu*10;
         
         x=a/mu;
         a=a-((int)x*mu);
         data[i]=0x30+((int)x);
         i++;
         digits--;
         mu=1;
     }   
     
    data[i]='\n';
}
    // Alistar configuracion de ADC
void start_adc(uint8_t frec, uint8_t isr, uint8_t Vref, uint8_t justRL) {
    ADCON0bits.ADON = 1;
    switch (frec) {
        case 1: // Fosc/2
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 0;
            break;
        case 2: // Fosc/8
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 0;
            break;
        case 3: // Fosc/32
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 1;
            break;
        case 4: // FRC 
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 1;
            break;
    }
    if (isr == 1) {
        PIE1bits.ADIE = 1; //Se habilita la interrupcion del ADC
        PIR1bits.ADIF = 0; //Se limpia la bandera del ADC
    }
    if (justRL == 0) {
        ADCON1bits.ADFM = 0; //se justifica a la izquierda
    } else {
        ADCON1bits.ADFM = 1; //se justifica a la derecha 
    }
    switch (Vref) {
        case 0: //Referencia en VDD y VSS
            ADCON1bits.VCFG0 = 0;
            ADCON1bits.VCFG1 = 0;
            break;
        case 1: //Referencia en Vref+ pin y VSS
            ADCON1bits.VCFG0 = 1;
            ADCON1bits.VCFG1 = 0;
            break;
        case 2: //Referencia en VDD y Vref- pin
            ADCON1bits.VCFG0 = 0;
            ADCON1bits.VCFG1 = 1;
            break;
        case 3: //Referencia en Vref+ pin y Vref- pin 
            ADCON1bits.VCFG0 = 1;
            ADCON1bits.VCFG1 = 1;
            break;
    }
}

// Empezar a colocar el valor del canal
void start_ch(uint8_t channel) { //Habilita los canales del ADC 
    switch (channel) {
        case 0: //Analogico en pin RA0
            ANSELbits.ANS0 = 1;
            break;
        case 1: //Analogico en pin RA1
            ANSELbits.ANS1 = 1;
            break;
        case 2: //Analogico en pin RA2
            ANSELbits.ANS2 = 1;
            break;
        case 3: //Analogico en pin RA3
            ANSELbits.ANS3 = 1;
            break;
        case 4: //Analogico en pin RA4
            ANSELbits.ANS4 = 1;
            break;
        case 5: //Analogico en pin RA5
            ANSELbits.ANS5 = 1;
            break;
        case 6: //Analogico en pin RA6
            ANSELbits.ANS6 = 1;
            break;
        case 7: //Analogico en pin RA7
            ANSELbits.ANS7 = 1;
            break;
        case 8: //Analogico en pin RB2
            ANSELHbits.ANS8 = 1;
            break;
        case 9: //Analogico en pin RB3
            ANSELHbits.ANS9 = 1;
            break;
        case 10: //Analogico en pin RB1
            ANSELHbits.ANS10 = 1;
            break;
        case 11: //Analogico en pin RB4
            ANSELHbits.ANS11 = 1;
            break;
        case 12: //Analogico en pin RB0
            ANSELHbits.ANS12 = 1;
            break;
        case 13: //Analogico en pin RB5
            ANSELHbits.ANS13 = 1;
            break;
    }
}


// Seleccionar Canal de Conversion
void Select_ch(uint8_t channel) {// se selecciona el canal analogico y se inicia la conversion
    switch (channel) {
        case 0: // AN0
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            break;
        case 1: // AN1
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            break;
        case 2: // AN2
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            break;
        case 3: // AN3
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            break;
        case 4: // AN4
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            break;
        case 5: // AN5
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            break;
        case 6: // AN6
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            break;
        case 7: // AN7
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            break;
        case 8: // AN8
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            break;
        case 9: // AN9
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            break;
        case 10: // AN10
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            break;
        case 11: // AN11
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            break;
        case 12: // AN12
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;
            break;
        case 13: // AN13
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;
            break;
        case 14: // CVref
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;
            break;
        case 15: // Fixed ref
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;
            break;
    }
    __delay_us(200); //es el tiempo recomendado de espera por cada cambio de canal
    ADCON0bits.GO = 1;
}

