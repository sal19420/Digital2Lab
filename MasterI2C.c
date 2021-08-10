/*
 * File:   MasterI2C.c
 * Author: Admin
 *
 * Created on 8 de agosto de 2021, 06:52 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Concatenar
#include <pic16f887.h>
#include "I2CL4M.h"
#include "ADCL4.h"
#include "LibreriasL4.h"
#include "LCDL4.h"


//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
char adc0[10];
char cont[10];
float conv0 = 0;
float conv1 = 0;
uint8_t var_adc0 = 0;
volatile uint8_t contador = 0;
char STH[3];
int8_t sensor;
char T[10];


//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    Lcd_Init();
    Lcd_Clear();
    while(1){

   
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        var_adc0 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x61);
        contador= I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x9A);
        I2C_Master_Write(0x00);
        __delay_ms(100);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        __delay_ms(200);
        I2C_Master_Write(0x9B);
        sensor= I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        
        
        
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("ADC:");
        Lcd_Set_Cursor(1, 8);
        Lcd_Write_String("CONT");
        Lcd_Set_Cursor(1, 13);
        Lcd_Write_String("TC");
        conv0 = 0;//se reinicia las cada ves que se inicia el proceso de enviar datos
        conv1 = 0;//tanto para la LCD como por UART.
//------------------------Mostrar datos via UART--------------------------------
        //-----------------------------Sensor 1---------------------------------
        conv0 = (var_adc0 / (float) 255)*5; //Se consigue el porcentaje con respecto al valor 
       //maximo que un puerto puede tener, despues se multiplica por 5 para conocer el voltaje actual del puerto                                          
        convert(adc0, conv0, 2);//se convierte el valor actual a un valor ASCII.
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(adc0);
        Lcd_Set_Cursor(2, 5);
        Lcd_Write_String("V");
        
        
        convert(cont, contador, 2);//se convierte el valor actual a un valor ASCII.
         Lcd_Set_Cursor(2, 7);
        Lcd_Write_String(cont);
        
        convert(T, sensor, 2);
         Lcd_Set_Cursor(2, 13);
        Lcd_Write_String(T);
       
        
        
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    PORTE = 0;
     //Configuracion del Oscilador
//    config_osc(7);
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS = 1;
    
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
}
int concat(int a, int b)
{
 
    char s1[20];
    char s2[20];
//    char s3[20]
 
    // Convert both the integers to string
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
//    sprintf(s2, "%d", c);
 
    // Concatenate both strings
    strcat(s1, s2);
 
    // Convert the concatenated string
    // to integer
    int c = atoi(s1);
 
    // return the formed integer
    return c;
}