    /*
     * File:   Librerias.c
     * Author: josuesalazar
     *
     * Created on July 18, 2021, 10:16 PM
     */


 #include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Librerias.h"
#define _XTAL_FREQ 8000000 

//    uint8_t ADC;
//    uint8_t low;
//    uint8_t high;
//
//    uint8_t tabla [16] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X67,
//    0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71};
//
    void config_osc(uint8_t frec){
        switch(frec){                   //31kHz
            case 0: 
                OSCCONbits.IRCF = 000;     
                break;   
            case 1:                     //125kHz
                OSCCONbits.IRCF = 001;     
                break;
            case 2:                     //250kHz
                OSCCONbits.IRCF = 010;     
                break;
            case 3:                     //500kHz
                OSCCONbits.IRCF = 011;     
                break;
            case 4:                     //1MHz
                OSCCONbits.IRCF = 100;     
                break;
            case 5:                     //2MHz
                OSCCONbits.IRCF = 101;     
                break;
            case 7:                     //8MHz
                OSCCONbits.IRCF = 111;     
                break;   
            default:                     //4MHz
                OSCCONbits.IRCF = 110;     
                break;            
        }
        OSCCONbits.SCS = 1; //se utiliza el reloj interno del sistema
    }

//    void config_tmr0(uint8_t prescaler){
//        switch(prescaler){              //1:2 rate
//            case 0: 
//                OPTION_REGbits.PS = 000;     
//                break;   
//            case 1:                     //1:4 rate
//                OPTION_REGbits.PS = 001;     
//                break;
//            case 2:                     //1:8 rate
//                OPTION_REGbits.PS = 010;     
//                break;
//            case 3:                     //1:16 rate
//                OPTION_REGbits.PS = 011;     
//                break;
//            case 4:                     //1:32 rate
//                OPTION_REGbits.PS = 100;     
//                break;
//            case 5:                     //1:64 rate
//                OPTION_REGbits.PS = 101;     
//                break;
//            case 7:                     //1:256 rate
//                OPTION_REGbits.PS = 111;     
//                break;   
//            default:                     //1:128 rate
//                OPTION_REGbits.PS = 110;     
//                break;            
//        }
//        OPTION_REGbits.T0CS = 0; //fuente del reloj interna Fosc/4  
//        OPTION_REGbits.PSA = 0;  //preescalar asignado a TMR0  
//    }
//
//    void config_ADC(uint8_t adcFrec){
//        switch(adcFrec){              //Fosc/2
//            case 0: 
//                ADCON0bits.ADCS = 00;     
//                break;   
//            case 1:                     //Fosc/8
//                ADCON0bits.ADCS = 01;     
//                break;
//            default:                     //Fosc/32
//                ADCON0bits.ADCS = 10;     
//                break;
//        }
//    //    ADCON1bits.ADFM = 0; //Leer bits más significativos; justificado izquierda
//        ADCON1bits.VCFG0 = 0; // VSS y VDD
//        ADCON1bits.VCFG1 = 0;     
//    }
//    void pasar_ADC (uint8_t dato) {
//        ADC = dato;
//    }
//
//    void LH(uint8_t dato) {
//        low =   dato & 0x0F;  
//        high  =   (dato >> 4) & 0x0F;   
//    }
//
//    void segmentos (uint8_t dato) {
//
//        PORTD = tabla[dato];
//
//    }
    
//    void Lcd_Port(char a) {
//        PORTD = a;
//}
//
//void Lcd_Cmd(char a) {
//    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
//    Lcd_Port(a);
//    EN = 1; // => E = 1
//    __delay_ms(4);
//    EN = 0; // => E = 0
//}
//
//void Lcd_Clear(void) {
//    Lcd_Cmd(0);
//    Lcd_Cmd(1);
//}
//
//void Lcd_Set_Cursor(char a, char b) {
//   char temp;
//    if (a == 1) {
//        temp = 0x80 + b - 1;
//        Lcd_Cmd(temp);
//    } else if (a == 2) {
//        temp = 0xC0 + b - 1;
//        Lcd_Cmd(temp);
//    }
//}
//
//void Lcd_Init(void) {
//    Lcd_Port(0x00);
//    __delay_ms(20);
//    Lcd_Cmd(0x30);
//    __delay_ms(5);
//    Lcd_Cmd(0x30);
//    __delay_ms(11);
//    Lcd_Cmd(0x30);
//    /////////////////////////////////////////////////////
//    Lcd_Cmd(0x38);
//    Lcd_Cmd(0x0C);
//    Lcd_Cmd(0x6);
//}
//
//void Lcd_Write_Char(char a) {
//    RS = 1; // => RS = 1
//    Lcd_Port(a); //Data transfer
//    EN = 1;
//    __delay_us(10);
//    EN = 0;
//}
//
//void Lcd_Write_String(char *a) {
//    int i;
//    for (i = 0; a[i] != '\0'; i++)
//        Lcd_Write_Char(a[i]);
//}
//
//void Lcd_Shift_Right(void) {
//    Lcd_Cmd(0x01);
//    Lcd_Cmd(0x0C);
//}
//
//void Lcd_Shift_Left(void) {
//    Lcd_Cmd(0x01);
//    Lcd_Cmd(0x08);
//}


//// Conversion de ADC 
//void convert(char *data,float a, int place) //definition
//{
//     int temp=a;
//     float x=0.0;
//     int digits=0;
//     int i=0,mu=1;
//     int j=0;
//     if(a<0)
//     {
//            a=a*-1;
//            data[i]='-';
//            i++;
//      }
//     //exponent component
//     while(temp!=0)
//     {
//         temp=temp/10;
//         digits++;          
//     }
//     while(digits!=0)
//     {
//         if(digits==1)mu=1;
//         else  for(j=2;j<=digits;j++)mu=mu*10;
//         
//         x=a/mu;
//         a=a-((int)x*mu);
//         data[i]=0x30+((int)x);
//         i++;
//         digits--;
//         mu=1;
//     }
//     //mantissa component
//     data[i]='.';
//     i++;
//     digits=0;
//     for(j=1;j<=place;j++)mu=mu*10;
//     x=(a-(int)a)*mu; //shift places
//     a=x;
//     temp=a;
//     x=0.0;
//     mu=1;
//     digits=place;
//     while(digits!=0)
//     {
//         if(digits==1)mu=1;
//         else  for(j=2;j<=digits;j++)mu=mu*10;
//         
//         x=a/mu;
//         a=a-((int)x*mu);
//         data[i]=0x30+((int)x);
//         i++;
//         digits--;
//         mu=1;
//     }   
//     
//    data[i]='\n';
//}
//    // Alistar configuracion de ADC
//void start_adc(uint8_t frec, uint8_t isr, uint8_t Vref, uint8_t justRL) {
//    ADCON0bits.ADON = 1;
//    switch (frec) {
//        case 1: // Fosc/2
//            ADCON0bits.ADCS0 = 0;
//            ADCON0bits.ADCS1 = 0;
//            break;
//        case 2: // Fosc/8
//            ADCON0bits.ADCS0 = 1;
//            ADCON0bits.ADCS1 = 0;
//            break;
//        case 3: // Fosc/32
//            ADCON0bits.ADCS0 = 0;
//            ADCON0bits.ADCS1 = 1;
//            break;
//        case 4: // FRC 
//            ADCON0bits.ADCS0 = 1;
//            ADCON0bits.ADCS1 = 1;
//            break;
//    }
//    if (isr == 1) {
//        PIE1bits.ADIE = 1; //Se habilita la interrupcion del ADC
//        PIR1bits.ADIF = 0; //Se limpia la bandera del ADC
//    }
//    if (justRL == 0) {
//        ADCON1bits.ADFM = 0; //se justifica a la izquierda
//    } else {
//        ADCON1bits.ADFM = 1; //se justifica a la derecha 
//    }
//    switch (Vref) {
//        case 0: //Referencia en VDD y VSS
//            ADCON1bits.VCFG0 = 0;
//            ADCON1bits.VCFG1 = 0;
//            break;
//        case 1: //Referencia en Vref+ pin y VSS
//            ADCON1bits.VCFG0 = 1;
//            ADCON1bits.VCFG1 = 0;
//            break;
//        case 2: //Referencia en VDD y Vref- pin
//            ADCON1bits.VCFG0 = 0;
//            ADCON1bits.VCFG1 = 1;
//            break;
//        case 3: //Referencia en Vref+ pin y Vref- pin 
//            ADCON1bits.VCFG0 = 1;
//            ADCON1bits.VCFG1 = 1;
//            break;
//    }
//}
//
//// Empezar a colocar el valor del canal
//void start_ch(uint8_t channel) { //Habilita los canales del ADC 
//    switch (channel) {
//        case 0: //Analogico en pin RA0
//            ANSELbits.ANS0 = 1;
//            break;
//        case 1: //Analogico en pin RA1
//            ANSELbits.ANS1 = 1;
//            break;
//        case 2: //Analogico en pin RA2
//            ANSELbits.ANS2 = 1;
//            break;
//        case 3: //Analogico en pin RA3
//            ANSELbits.ANS3 = 1;
//            break;
//        case 4: //Analogico en pin RA4
//            ANSELbits.ANS4 = 1;
//            break;
//        case 5: //Analogico en pin RA5
//            ANSELbits.ANS5 = 1;
//            break;
//        case 6: //Analogico en pin RA6
//            ANSELbits.ANS6 = 1;
//            break;
//        case 7: //Analogico en pin RA7
//            ANSELbits.ANS7 = 1;
//            break;
//        case 8: //Analogico en pin RB2
//            ANSELHbits.ANS8 = 1;
//            break;
//        case 9: //Analogico en pin RB3
//            ANSELHbits.ANS9 = 1;
//            break;
//        case 10: //Analogico en pin RB1
//            ANSELHbits.ANS10 = 1;
//            break;
//        case 11: //Analogico en pin RB4
//            ANSELHbits.ANS11 = 1;
//            break;
//        case 12: //Analogico en pin RB0
//            ANSELHbits.ANS12 = 1;
//            break;
//        case 13: //Analogico en pin RB5
//            ANSELHbits.ANS13 = 1;
//            break;
//    }
//}
//
//
//// Seleccionar Canal de Conversion
//void Select_ch(uint8_t channel) {// se selecciona el canal analogico y se inicia la conversion
//    switch (channel) {
//        case 0: // AN0
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 1: // AN1
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 2: // AN2
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 3: // AN3
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 4: // AN4
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 5: // AN5
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 6: // AN6
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 7: // AN7
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 0;
//            break;
//        case 8: // AN8
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 9: // AN9
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 10: // AN10
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 11: // AN11
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 0;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 12: // AN12
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 13: // AN13
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 0;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 14: // CVref
//            ADCON0bits.CHS0 = 0;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 1;
//            break;
//        case 15: // Fixed ref
//            ADCON0bits.CHS0 = 1;
//            ADCON0bits.CHS1 = 1;
//            ADCON0bits.CHS2 = 1;
//            ADCON0bits.CHS3 = 1;
//            break;
//    }
//    __delay_us(5); //es el tiempo recomendado de espera por cada cambio de canal
//    ADCON0bits.GO = 1;
//}
