/*
 * File:   Lab05.c
 * Author: Admin
 *
 * Created on 15 de agosto de 2021, 10:20 PM
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
#include"ADC.h"




#define _XTAL_FREQ 8000000 
#define _tmr0_value 217

//**********Variables***********
//uint8_t canal_act = 0;
volatile uint8_t var_adc0 = 0;
volatile uint8_t var_adc1 = 0;
char dato0[10];
char adc1[10];
float conv0 = 0;
float conv1 = 0;
char cen, dec, uni;
char var;
char con;
uint8_t contador;
int full;

 //**********Prototipos*********
 void setup(void);
 void Eusart(void);
 void putch(char data);
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
    if (RBIF == 1){    //Contador
        
        
        if (RB0 == 1){              //Verificamos cual boton se presiona
            contador++;   //Si es RB0 incrementamos
            contador = contador & 0X0F;
            PORTA = contador;
        }
        
        if (RB1 == 1){              //Si es RB1 decrementamos
            contador--;
            contador = contador & 0X0F;
            PORTA = contador; 
        }
        
        INTCONbits.RBIF = 0;        //Reiniciamos la interupción
    }
}
void main(void) {
     setup();
    
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        Eusart();
        PORTD = full;
        convert(dato0,contador,2);
        
}
    return;
}
void setup(void){
    ANSEL = 0X00;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0X03;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    
     //Configuracion del Oscilador
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS = 1;
    
   
     //Configuracion Interupciones
    INTCONbits.GIE   = 1;       //Activamos las interupciones on change y del TMR0
    INTCONbits.PEIE  = 1;
    INTCONbits.RBIE  = 1;
    INTCONbits.RBIF  = 0;

    
    //Configuracion Puerto B
    IOCBbits.IOCB0   = 1;       //Activamos en RB0 y RB1 la interupcion on change
    IOCBbits.IOCB1   = 1;
    
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
    
}
void putch(char data){
    while (TXIF == 0);      //Esperar a que se pueda enviar un nueva caracter
    TXREG = data;           //Transmitir un caracter
    return;
}

void Eusart (void) {
    __delay_ms(100);         //El Eusart
   printf("\rContador en decimales: \r");
   __delay_ms(100);
     printf(dato0);
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
