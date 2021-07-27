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

