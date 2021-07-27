
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Librerias_H
#define	Librerias_H

#pragma config FOSC = INTRC_NOCLKOUT
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


void config_osc(uint8_t frec);


#endif	/* XC_HEADER_TEMPLATE_H */

