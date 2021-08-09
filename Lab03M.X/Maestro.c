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
#include <string.h> // Concatenar
#include "LibreriasL3.h"
#include "ADCL3.h"
#include "USARTL3.h"



#define _XTAL_FREQ 8000000 
#define _tmr0_value 217

//**********Variables***********
//uint8_t canal_act = 0;
volatile uint8_t var_adc0 = 0;
volatile uint8_t var_adc1 = 0;
char adc0[10];
char adc1[10];
float conv0 = 0;
float conv1 = 0;
char cen, dec, uni;
char var;
char con;
int full;

 //**********Prototipos*********
 void config(void);
 void Eusart(void);
 void putch(char data);

 
void main(void) {

    config();
    while(1){
        
        PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(1);
        var_adc0 = spiRead();
//       PORTB = sensor1;
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(2);
       var_adc1 = spiRead();
//       PORTD = sensor2;
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect
       
       
       conv0 = 0;
       conv1 = 0;
       conv0 = (var_adc0 / (float) 255)*5;
       conv1 = (var_adc1 / (float) 255)*5;
       
       convert(adc0, conv0, 2);
       convert(adc1, conv1, 2);
       Eusart();
        PORTB = full;
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
   
    //Configuracion de TX y RX
    TXSTAbits.SYNC  = 0;    //Modo asincrono
    TXSTAbits.BRGH  = 1;    //Activamos la alta velocidad del Baud rate
    
    BAUDCTLbits.BRG16   = 1;    //Utilizamos los 16 bits del Baud rate
    
    SPBRG   = 207;  //Elegimos el baud rate 9600
    SPBRGH  = 0;
    
    RCSTAbits.SPEN  = 1;    //Activamos los puertos seriales
    RCSTAbits.RX9   = 0;    //No utilizamos los nueve bits
    RCSTAbits.CREN  = 1;    //Activamos la recepción continua
    
    TXSTAbits.TXEN  = 1;    //Activamos la transmición
   return;
}

//char division (char valor){
//    hundreds = valor/50;//esto me divide entre 100 y se queda con el entero
//    residuo = valor%100; //el residuo de lo que estoy operando
//    tens = residuo/10; 
//    units = residuo%10; //se queda con las units de las tens
//    // Se les suma 47 para que me den al valor requerido
//    hundreds = hundreds + 48;
//    tens = tens + 48;
//    units = units + 48;
//} 



void putch(char data){
    while (TXIF == 0);      //Esperar a que se pueda enviar un nueva caracter
    TXREG = data;           //Transmitir un caracter
    return;
}

void Eusart (void) {
    __delay_ms(100);         //El Eusart
   printf("\rSensor 1: \r");
   __delay_ms(100);
     printf(adc0);
   __delay_ms(100);
   printf("\r---------------\r");
   
   
   __delay_ms(100);
   printf("\rSensor 2: \r");
   __delay_ms(100);
   printf(adc1);
   __delay_ms(100);
   printf("\r---------------\r");
   
    printf("Ingresar Centena: Rango(0-2)\r");
      defensa1:  
       while(RCIF == 0);
        cen = RCREG -48;  

       while(RCREG > '2'){ 
           goto defensa1;
       }
    
    printf("Ingresar Decenas: \r");
      defensa2:
        while(RCIF == 0); 
         dec = RCREG -48; 

        if(cen == 2){
           while(RCREG > '5'){
               goto defensa2;
           }
       }

    printf("Ingresar Unidades: \r");
      defensa3:
       while(RCIF == 0); 
        uni = RCREG - 48;

       if(cen == 2 && dec == 5){
           while(RCREG > '5'){
               goto defensa3;
           }
       }
      con = concat(cen, dec);
      full = concat(con, uni);
      __delay_ms(250);
    printf("El numero elegido es: %d", full);

   return;
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