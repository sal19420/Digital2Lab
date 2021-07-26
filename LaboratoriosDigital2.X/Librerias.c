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

    uint8_t ADC;
    uint8_t low;
    uint8_t high;

    uint8_t tabla [16] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X67,
    0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71};

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

    void config_tmr0(uint8_t prescaler){
        switch(prescaler){              //1:2 rate
            case 0: 
                OPTION_REGbits.PS = 000;     
                break;   
            case 1:                     //1:4 rate
                OPTION_REGbits.PS = 001;     
                break;
            case 2:                     //1:8 rate
                OPTION_REGbits.PS = 010;     
                break;
            case 3:                     //1:16 rate
                OPTION_REGbits.PS = 011;     
                break;
            case 4:                     //1:32 rate
                OPTION_REGbits.PS = 100;     
                break;
            case 5:                     //1:64 rate
                OPTION_REGbits.PS = 101;     
                break;
            case 7:                     //1:256 rate
                OPTION_REGbits.PS = 111;     
                break;   
            default:                     //1:128 rate
                OPTION_REGbits.PS = 110;     
                break;            
        }
        OPTION_REGbits.T0CS = 0; //fuente del reloj interna Fosc/4  
        OPTION_REGbits.PSA = 0;  //preescalar asignado a TMR0  
    }

    void config_ADC(uint8_t adcFrec){
        switch(adcFrec){              //Fosc/2
            case 0: 
                ADCON0bits.ADCS = 00;     
                break;   
            case 1:                     //Fosc/8
                ADCON0bits.ADCS = 01;     
                break;
            default:                     //Fosc/32
                ADCON0bits.ADCS = 10;     
                break;
        }
    //    ADCON1bits.ADFM = 0; //Leer bits más significativos; justificado izquierda
        ADCON1bits.VCFG0 = 0; // VSS y VDD
        ADCON1bits.VCFG1 = 0;     
    }
    void pasar_ADC (uint8_t dato) {
        ADC = dato;
    }

    void LH(uint8_t dato) {
        low =   dato & 0x0F;  
        high  =   (dato >> 4) & 0x0F;   
    }

    void segmentos (uint8_t dato) {

        PORTD = tabla[dato];

    }
    
    void Lcd_Port(char a) {
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init(void) {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a) {
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1; // => RS = 1
    Lcd_Port(y >> 4); //Data transfer
    EN = 1;
    __delay_ms(40);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    __delay_ms(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}
