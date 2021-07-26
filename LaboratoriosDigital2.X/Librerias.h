
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Librerias_H
#define	Librerias_H

#pragma config FOSC = INTRC_NOCLKOUT
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#define RS PORTEbits.RE0
#define EN PORTEbits.RE2
#define RW PORTEbits.RE1    
#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D3 PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

void config_osc(uint8_t frec);
//void config_tmr0(uint8_t prescaler);
//void config_ADC(uint8_t adcFrec);
//void pasar_ADC (uint8_t dato);
//void LH (uint8_t dato);
//void segmentos (uint8_t dato);

// LCD

void Lcd_Port(char a);

void Lcd_Cmd(char a);

void Lcd_Clear(void);

void Lcd_Set_Cursor(char a, char b);

void Lcd_Init(void);

void Lcd_Write_Char(char a);

void Lcd_Write_String(char *a);

void Lcd_Shift_Right(void);

void Lcd_Shift_Left(void);

////COnversion ADC 
//void convert(char *data,float a, int place);
//void start_adc(uint8_t frec, uint8_t isr, uint8_t Vref, uint8_t justRL);
//void Select_ch(uint8_t channel);
//void start_ch(uint8_t channel);

#endif	/* XC_HEADER_TEMPLATE_H */

