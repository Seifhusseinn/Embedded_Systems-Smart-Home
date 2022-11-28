#include "LED_Interface.h"

void LED_Init(uint8 portno, uint8 pinno) {
    DIO_SetPinDirection(portno, pinno, OUTPUT);
}

void LED_On(uint8 portno, uint8 pinno) {
    DIO_SetPinValue(portno, pinno, HIGH);
}

void LED_Off(uint8 portno, uint8 pinno) {
    DIO_SetPinValue(portno, pinno, LOW);
}

void LED_Toggle(uint8 portno, uint8 pinno) {
    if (DIO_RdPinValue(portno, pinno) == LOW)
        DIO_SetPinValue(portno, pinno, HIGH);
    else
        DIO_SetPinValue(portno, pinno, LOW);   
}

uint8 LED_Rdstatus(uint8 portno, uint8 pinno) {
    return DIO_RdPinValue(portno, pinno);
}