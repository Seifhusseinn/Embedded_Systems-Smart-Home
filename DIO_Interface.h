#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "std_types.h"
#include "DIO_Register.h"
#include "DIO_Config.h"
#include "Bit_Math.h"

#define PORTA_ 0 
#define PORTB_ 1
#define PORTC_ 2 
#define PORTD_ 3 

#define INPUT 0 
#define OUTPUT 1

#define LOW     0
#define HIGH    1

void DIO_Init(void);
void DIO_SetPinDirection(uint8 portno, uint8 pinno, uint8 state);
void DIO_SetPortDirection(uint8 portno, uint8 state);
void DIO_SetPinValue(uint8 portno, uint8 pinno, uint8 value);
void DIO_SetPortValue(uint8 portno, uint8 value);
uint8 DIO_RdPinValue(uint8 portno, uint8 pinno);
uint8 DIO_RdPortValue(uint8 portno);

#endif