#include "DIO_Interface.h"


void DIO_Init(void) {
    DDRA_REG = DDRA_INIT;
    DDRB_REG = DDRB_INIT;
    DDRC_REG = DDRC_INIT;
    DDRD_REG = DDRD_INIT;
    PORTA_REG = PORTA_INIT; 
    PORTB_REG = PORTB_INIT;
    PORTC_REG = PORTC_INIT;
    PORTD_REG = PORTD_INIT;
} 

void DIO_SetPinDirection(uint8 portno, uint8 pinno, uint8 state) {

    if (state == INPUT) {
        switch(portno) {
            case PORTA_: CLR_BIT(DDRA_REG, pinno); break;
            case PORTB_: CLR_BIT(DDRB_REG, pinno); break;
            case PORTC_: CLR_BIT(DDRC_REG, pinno); break;
            case PORTD_: CLR_BIT(DDRD_REG, pinno); break;       
            default: break;  
        }
    }
    else if (state == OUTPUT) {
        switch(portno) {
            case PORTA_: SET_BIT(DDRA_REG, pinno); break;
            case PORTB_: SET_BIT(DDRB_REG, pinno); break;
            case PORTC_: SET_BIT(DDRC_REG, pinno); break;
            case PORTD_: SET_BIT(DDRD_REG, pinno); break;    
            default: break;     
        }
    }
}

void DIO_SetPortDirection(uint8 portno, uint8 state) {
    switch(portno) {
        case PORTA_: DDRA_REG = state; break;
        case PORTB_: DDRB_REG = state; break;
        case PORTC_: DDRC_REG = state; break;
        case PORTD_: DDRD_REG = state; break;        
        default: break; 
        }
}

void DIO_SetPinValue(uint8 portno, uint8 pinno, uint8 value) {
    if (value == LOW) {
        switch(portno) {
            case PORTA_: CLR_BIT(PORTA_REG, pinno); break;
            case PORTB_: CLR_BIT(PORTB_REG, pinno); break;
            case PORTC_: CLR_BIT(PORTC_REG, pinno); break;
            case PORTD_: CLR_BIT(PORTD_REG, pinno); break;   
            default: break;      
        }
    }
    else if (value == HIGH) {
        switch(portno) {
            case PORTA_: SET_BIT(PORTA_REG, pinno); break;
            case PORTB_: SET_BIT(PORTB_REG, pinno); break;
            case PORTC_: SET_BIT(PORTC_REG, pinno); break;
            case PORTD_: SET_BIT(PORTD_REG, pinno); break;    
            default: break;     
        }
    }
}

void DIO_SetPortValue(uint8 portno, uint8 value) { 
    switch(portno) {
        case PORTA_: PORTA_REG = value; break;
        case PORTB_: PORTB_REG = value; break;
        case PORTC_: PORTC_REG = value; break;
        case PORTD_: PORTD_REG = value; break;      
        default: break;  
        }
}

uint8 DIO_RdPinValue(uint8 portno, uint8 pinno) {
    switch(portno) {
            case PORTA_: return RD_BIT(PINA_REG, pinno); break;
            case PORTB_: return RD_BIT(PINB_REG, pinno); break;
            case PORTC_: return RD_BIT(PINC_REG, pinno); break;
            case PORTD_: return RD_BIT(PIND_REG, pinno); break;     
            default: break;    
        } 
}

uint8 DIO_RdPortValue(uint8 portno) { 
    switch(portno) {
            case PORTA_: return PINA_REG; break;
            case PORTB_: return PINB_REG; break;
            case PORTC_: return PINC_REG; break;
            case PORTD_: return PIND_REG; break;        
            default: break; 
    } 
}