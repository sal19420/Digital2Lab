/*
 * File:   Librerias.c
 * Author: Admin
 *
 * Created on 31 de julio de 2021, 04:58 PM
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


void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    
    SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()
{
    while ( !SSPSTATbits.BF ); // Wait for Data Receive complete
}

void spiWrite(char dat)  //Write data to SPI bus
{
    SSPBUF = dat;
}

unsigned spiDataReady() //Check whether the data is ready to read
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char spiRead() //REad the received data
{
    spiReceiveWait();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}
